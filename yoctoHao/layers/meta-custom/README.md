# meta-custom Yocto Layer

A custom Yocto Project layer for embedding project-specific recipes, machine configurations, and customizations.

## Layer Structure

```
meta-custom/
├── conf/
│   └── layer.conf           # Layer configuration and metadata
├── recipes-core/            # Core recipe customizations
├── recipes-apps/            # Application recipes
└── README.md               # This file
```

## Quick Start Guide

### Step 1: Add the Layer to Your Yocto Build

Navigate to your Yocto build directory and add this layer:

```bash
cd /path/to/your/yocto/build
source ../layers/openembedded-core/oe-init-build-env .
```
. /home/aelz/bitbake-builds/poky-master/buildtools/environment-setup-x86_64-pokysdk-linux
Then add the layer to `bblayers.conf`:

```bash
# Edit conf/bblayers.conf
bitbake-layers add-layer /path/to/meta-custom
```

Verify the layer was added:
```bash
bitbake-layers show-layers | grep meta-custom
```

Expected output:
```
meta-custom  /path/to/meta-custom
```

### Step 2: Include Applications in Your Image

Edit your build directory's `conf/local.conf` to include custom applications:

```bash
# Add this line to conf/local.conf
IMAGE_INSTALL:append = " demo"
```

This ensures the demo application will be installed in your image.

### Step 3: Build the Image

Build a Yocto image with the demo application included:

```bash
bitbake core-image-sato
```

For other images, you can use:
- `bitbake core-image-minimal` – Minimal image
- `bitbake core-image-full-cmdline` – Full command-line image
- `bitbake core-image-x11` – X11 graphical image

The build process will:
1. Parse all recipes from all layers
2. Build all dependencies
3. Compile and package the demo application
4. Create the final filesystem image

Build output will be in: `tmp/deploy/images/<machine>/`

### Step 4: Run the Image

#### Option A: QEMU (Emulation)

To run the built image in QEMU:

```bash
#runqemu qemux86-64 wic
runqemu snapshot
ip addr
ssh  @ip_addr
```

Once booted, log in (no password required) and run demo:
```bash
$ demo
```

#### Option B: Extract and Run Directly

To extract and test the demo binary:

```bash
# Find the rootfs
ls tmp/deploy/images/qemux86-64/core-image-sato-*

# Mount or extract the image
# The demo executable will be at /usr/bin/demo in the rootfs
```

### Step 5: Execute the Demo Application

Once the image is running (in QEMU or on target hardware):

```bash
# Connect to the system and run demo
demo

# Expected output:
# Demo application demonstrating UDS Socket communication
# Loading dynamic libraries...
# Starting UDS server...
# [demo running...]
```

To view demo help or options:
```bash
demo --help
```

## Layer Configuration

- **LAYERVERSION**: 1 (increment when making breaking changes)
- **LAYERPRIORITY**: 6 (default priority for recipe precedence)
- **LAYERDEPENDS**: Depends on `core` layer
- **LAYERSERIES_COMPAT**: Compatible with multiple Yocto releases

## Creating Recipes

### Recipe Organization

Recipes should be organized by category in `recipes-*` directories:

- `recipes-core/` – Core system components and libraries
- `recipes-apps/` – Application packages
- `recipes-kernel/` – Kernel recipes and modules
- `recipes-bsp/` – Board support package recipes
- `recipes-connectivity/` – Network and connectivity packages

### Example Recipe Structure

```
recipes-apps/myapp/
├── myapp_1.0.bb
├── myapp_1.1.bb
└── files/
    ├── 0001-fix-build.patch
    └── myapp.service
```

### Creating a New Recipe

1. Create the recipe directory:
   ```bash
   mkdir -p recipes-apps/myapp
   ```

2. Create the recipe file `myapp_1.0.bb`:
   ```bitbake
   SUMMARY = "My Custom Application"
   DESCRIPTION = "A brief description of the application"
   HOMEPAGE = "https://example.com"
   LICENSE = "MIT"
   
   SRC_URI = "git://github.com/example/myapp.git;protocol=https;branch=main"
   SRCREV = "abc123def456..."
   
   S = "${WORKDIR}/git"
   
   inherit autotools
   
   DEPENDS = "some-library"
   RDEPENDS_${PN} = "runtime-dependency"
   ```

3. Add patches and files to `recipes-apps/myapp/files/`

## Machine Customizations

To add machine-specific configurations, create `conf/machine/` subdirectory:

```bash
mkdir -p conf/machine
```

Add machine definitions (e.g., `conf/machine/my-machine.conf`) with board-specific settings.

## Best Practices

1. **Use version numbers**: `recipe_version.bb` format aids in recipe management
2. **License declarations**: Always specify the LICENSE variable
3. **Documentation**: Add SUMMARY and DESCRIPTION to all recipes
4. **Source management**: Use SRCREV for git sources to ensure reproducibility
5. **Patches**: Keep patches in the `files/` directory and reference them in SRC_URI
6. **Dependencies**: List all DEPENDS and RDEPENDS explicitly

## Layer Compatibility

This layer is compatible with Yocto releases:
- Scarthgap (2024.12)
- Nanbield (2024.06)
- Mickledore (2023.12)
- Langdale (2023.06)
- Kirkstone (2022.12)
- Honister (2021.11)
- Hardknott (2021.04)
- Gatesgarth (2020.10)
- Dunfell (2020.05)

## Included Recipes

### demo (1.0)

**Description**: UDS Socket communication example application

**Location**: `recipes-apps/demo/demo_1.0.bb`

**Source**: `/home/aelz/repa/aelzSamples/demo`

**Features**:
- Demonstrates Unix Domain Socket (UDS) communication
- Forward list data structure implementation
- Dynamic library loading
- Multi-threaded UDS server

**Build Requirements**:
- C++20 compiler support
- libpthread

**Installation**: `/usr/bin/demo`

## Common Tasks

### Build a single recipe
```bash
bitbake demo
```

### Build with your layer
```bash
bitbake core-image-minimal
```

### Debug a recipe
```bash
bitbake -e demo | grep SUMMARY
```

### Show recipe dependencies
```bash
bitbake -g demo
# Generates task-depends.dot showing dependency graph
```

### Clean a recipe build
```bash
bitbake -c clean demo
```

### Clean and rebuild
```bash
bitbake -c cleanall demo
bitbake demo
```

## Troubleshooting

### Recipe Not Found
If you get `ERROR: Nothing PROVIDES demo`, verify:
1. Layer is added to `bblayers.conf`
2. Recipe file exists: `recipes-apps/demo/demo_1.0.bb`
3. Run `bitbake-layers show-recipes | grep demo`

### Build Fails with Permission Errors
This layer requires write access to source directories during build. Ensure:
- Build directory has write permissions
- Source paths are accessible
- No other bitbake instances are running

### Image Build Takes Too Long
- First build can take 30-90 minutes depending on system
- Subsequent builds use state cache (sstate) for faster rebuilds
- To speed up: increase parallel tasks in `local.conf`:
  ```bitbake
  BB_NUMBER_THREADS = "8"
  PARALLEL_MAKE = "-j 8"
  ```

### QEMU Won't Start
Ensure QEMU is installed:
```bash
sudo apt-get install qemu-system-x86
```

And the image exists:
```bash
ls tmp/deploy/images/qemux86-64/core-image-sato-qemux86-64.wic*
```

## Documentation References

- [Yocto Project Manual](https://docs.yoctoproject.org/)
- [BitBake User Manual](https://docs.yoctoproject.org/bitbake/)
- [Board Support Package (BSP) Developer's Guide](https://docs.yoctoproject.org/bsp-guide/)
- [Layer Development Manual](https://docs.yoctoproject.org/dev-manual/)

## Support

For issues or questions about this layer, refer to the Yocto Project documentation or community resources.
