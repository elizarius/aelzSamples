SUMMARY = "Demo application - UDS Socket communication example"
DESCRIPTION = "A C++ application demonstrating Unix Domain Socket (UDS) communication \
with forward list data structures and dynamic library loading."
HOMEPAGE = "https://github.com/example/demo"
AUTHOR = "Alexander Elizarov <al.elizarov@gmail.com>"
LICENSE = "MIT"

# Runtime dependencies
RDEPENDS_${PN} = "libc libstdc++"

# Skip QA check for hardcoded build paths (debug symbols contain -g paths)
OEQA_BUILDPATHS_SKIP = "/home/aelz"

# Skip all standard build tasks - use pre-built binary
do_fetch[noexec] = "1"
do_unpack[noexec] = "1"
do_patch[noexec] = "1"
do_configure[noexec] = "1"
do_prepare_recipe_sysroot[noexec] = "1"
do_compile[noexec] = "1"

# Install the pre-built executable from the source directory
do_install() {
    install -d ${D}${bindir}
    install -m 0755 /home/aelz/repa/aelzSamples/demo/demo ${D}${bindir}/demo
}

# Package contents
FILES_${PN} = "${bindir}/demo"

# Additional metadata
SECTION = "console/utils"
