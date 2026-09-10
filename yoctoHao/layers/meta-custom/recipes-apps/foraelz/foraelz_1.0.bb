SUMMARY = "For loop demonstration application"
DESCRIPTION = "A simple C++ application demonstrating different for loop styles in C++"
HOMEPAGE = "https://github.com/example/foraelz"
AUTHOR = "Alexander Elizarov <al.elizarov@gmail.com>"
LICENSE = "MIT"

# Runtime dependencies
RDEPENDS_${PN} = "libc libstdc++"

# Skip QA check for hardcoded build paths (debug symbols contain -g paths)
OEQA_BUILDPATHS_SKIP = "/home/aelz"

# Skip fetch, unpack, patch, configure - source is local
do_fetch[noexec] = "1"
do_unpack[noexec] = "1"
do_patch[noexec] = "1"
do_configure[noexec] = "1"

# Compile the for.cpp file with full static linking
do_compile() {
    g++ -static -o foraelz /home/aelz/repa/aelzSamples/es/for.cpp -std=c++11
}

# Install the compiled executable
do_install() {
    install -d ${D}${bindir}
    install -m 0755 foraelz ${D}${bindir}/foraelz
}

# Package contents
FILES_${PN} = "${bindir}/foraelz"

# Additional metadata
SECTION = "console/utils"
