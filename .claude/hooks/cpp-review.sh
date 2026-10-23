#!/usr/bin/env bash
# PostToolUse hook: applies the secure C++ rules to edited C++ files.
# Mode is set by CPP_REVIEW_MODE: off | remind | auto
set -uo pipefail

MODE="${CPP_REVIEW_MODE:-remind}"
[ "$MODE" = "off" ] && exit 0

# Prevents the headless reviewer's own edits from starting another review
[ "${CPP_REVIEW_RUNNING:-0}" = "1" ] && exit 0

FILE=$(jq -r '.tool_input.file_path // empty')

case "$FILE" in
  *.cpp|*.cc|*.cxx|*.c++|*.h|*.hh|*.hpp|*.hxx) ;;
  *) exit 0 ;;
esac

case "$MODE" in
  remind)
    echo "C++ file edited: $FILE. Check it against .claude/rules/secure-cpp.md and fix any violations." >&2
    exit 2   # exit 2 sends this message to Claude
    ;;
  auto)
    LOG="$CLAUDE_PROJECT_DIR/.claude/hooks/cpp-review.log"
    CPP_REVIEW_RUNNING=1 nohup claude -p --agent cpp-secure-reviewer \
      --permission-mode acceptEdits \
      "Review and fix secure-coding violations in $FILE" >>"$LOG" 2>&1 &
    exit 0
    ;;
esac
exit 0