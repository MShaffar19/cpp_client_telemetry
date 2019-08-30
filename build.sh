#!/bin/bash

export PATH=/usr/local/bin:$PATH

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo "Current directory: $DIR"
cd $DIR

export NOROOT=$NOROOT

if [ "$1" == "clean" ]; then
 rm -f CMakeCache.txt *.cmake
 rm -rf out
 rm -rf .buildtools
# make clean
fi

if [ "$1" == "noroot" ] || [ "$2" == "noroot" ]; then
export NOROOT=true
fi

# Install build tools and recent sqlite3
FILE=.buildtools
OS_NAME=`uname -a`
if [ ! -f $FILE ]; then
case "$OS_NAME" in
 *Darwin*) tools/setup-buildtools-mac.sh ;;
 *Linux*)  [[ -z "$NOROOT" ]] && sudo tools/setup-buildtools.sh || echo "No root: skipping build tools installation." ;;
 *)        echo "WARNING: unsupported OS $OS_NAME , skipping build tools installation.."
esac
# Assume that the build tools have been successfully installed
echo > $FILE
fi

if [ -f /usr/bin/gcc ]; then
echo "gcc   version: `gcc --version`"
fi

if [ -f /usr/bin/clang ]; then
echo "clang version: `clang --version`"
fi

# Skip Version.hpp changes
# git update-index --skip-worktree lib/include/public/Version.hpp

#rm -rf out
mkdir -p out
cd out

# .tgz package
CMAKE_PACKAGE_TYPE=tgz

# .deb package
if [ -f /usr/bin/dpkg ]; then
export CMAKE_PACKAGE_TYPE=deb
fi

# .rpm package
if [ -f /usr/bin/rpmbuild ]; then
export CMAKE_PACKAGE_TYPE=rpm
fi


# Fail on error
set -e

if [ "$2" == "release" ]; then
# TODO: pass custom build flags?
  cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_PACKAGE_TYPE=$CMAKE_PACKAGE_TYPE -DCMAKE_CXX_FLAGS="-Wignored-qualifiers -Wreorder" ..
# TODO: strip symbols to minimize
else
  cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PACKAGE_TYPE=$CMAKE_PACKAGE_TYPE -DCMAKE_CXX_FLAGS="-Wignored-qualifiers -Wreorder" ..
fi

# Build all
# TODO: what are the pros and cons of using 'make' vs 'cmake --build' ?
#make
cmake --build .

# No fail on error
set +e

# Remove old package
rm -f *.deb *.rpm

# Build new package
make package

# Debian / Ubuntu / Raspbian
if [ -f /usr/bin/dpkg ]; then
# Install new package
[[ -z "$NOROOT" ]] && sudo dpkg -i *.deb || echo "No root: skipping package deployment."
fi

# RedHat / CentOS
if [ -f /usr/bin/rpmbuild ]; then
[[ -z "$NOROOT" ]] && sudo rpm -i --force -v *.rpm || echo "No root: skipping package deployment."
fi

# Install SDK headers and lib to /usr/local
#
## TODO: [MG] - fix this section for shared library
## strip --strip-unneeded out/lib/libmat.so
## strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag out/lib/libmat.so

if [ "$CMAKE_PACKAGE_TYPE" == "tgz" ]; then
cd ..
MATSDK_INSTALL_DIR="${MATSDK_INSTALL_DIR:-/usr/local}"
echo "+-----------------------------------------------------------------------------------+"
echo " This step may prompt for your sudo password to deploy SDK to $MATSDK_INSTALL_DIR  "
echo "+-----------------------------------------------------------------------------------+"
sudo ./install.sh $MATSDK_INSTALL_DIR
fi
