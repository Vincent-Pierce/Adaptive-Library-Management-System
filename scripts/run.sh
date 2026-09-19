#!/bin/bash
set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

echo "Running build, test, and diagram scripts..."

"$SCRIPT_DIR/build.sh"
"$SCRIPT_DIR/test.sh"
"$SCRIPT_DIR/diagram.sh"