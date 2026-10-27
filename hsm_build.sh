#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# --- Configuration ---
IMAGE_NAME="build-hsm"
# Get the absolute path of the current directory to ensure Docker volumes work correctly
WORK_DIR=$(pwd)

# --- 1. Argument Validation ---
if [ $# -lt 1 ]; then
    echo "Usage: $0 <HSM_PIN> [GROUP_ID PERMS]..."
    echo "Example: $0 123456 0x11 R 0x22 WC 0x33"
    exit 1
fi

# Get the HSM PIN (First Argument)
HSM_PIN=$1
shift

# --- 2. Permission Parsing Loop ---
PERMISSIONS_LIST=""

# Function to format input "RWC" into "RWC", "R--", "-WC", etc.
normalize_perms() {
    local input=$(echo "$1" | tr '[:lower:]' '[:upper:]')
    local p_str=""
    
    # Position 1: Read
    if [[ $input == *"R"* ]]; then p_str+="R"; else p_str+="-"; fi
    # Position 2: Write
    if [[ $input == *"W"* ]]; then p_str+="W"; else p_str+="-"; fi
    # Position 3: Custom/Execute
    if [[ $input == *"C"* ]]; then p_str+="C"; else p_str+="-"; fi
    
    echo "$p_str"
}

while (( "$#" )); do
    GID=$1
    RAW_PERM=""
    
    # Peek at the next argument to see if it is a Permission or the next Group ID
    NEXT_ARG=$2
    
    # Logic: If next arg exists AND contains only characters [R,W,C,-], treat as Perms.
    # Otherwise, assume it's the next Group ID (or end of list) and current perm is blank.
    if [[ -n "$NEXT_ARG" && "$NEXT_ARG" =~ ^[RWCrwc-]+$ ]]; then
        RAW_PERM=$NEXT_ARG
        shift 2
    else
        # Next arg is missing or looks like a Group ID (digits/hex)
        RAW_PERM=""
        shift 1
    fi

    # Format the permissions (e.g., "R" -> "R--")
    FORMATTED_PERMS=$(normalize_perms "$RAW_PERM")
    
    # Append to the list (colon-separated)
    if [ -z "$PERMISSIONS_LIST" ]; then
        PERMISSIONS_LIST="${GID}=${FORMATTED_PERMS}"
    else
        PERMISSIONS_LIST="${PERMISSIONS_LIST}:${GID}=${FORMATTED_PERMS}"
    fi
done

echo "[*] Starting Docker Build..."
echo "    HSM_PIN:     [HIDDEN]"
echo "    PERMISSIONS: $PERMISSIONS_LIST"

# --- 3. Command Construction & Execution ---

# Construct the command array for cleaner printing and execution
# We use an array to handle spaces in paths correctly
CMD=(
    docker run --rm
    -v "$WORK_DIR/firmware":/hsm
    -v "$WORK_DIR"/global.secrets:/secrets/global.secrets:ro
    -v "$WORK_DIR/build":/out
    -e HSM_PIN="$HSM_PIN"
    -e PERMISSIONS="$PERMISSIONS_LIST"
    "$IMAGE_NAME"
)

echo "[*] Executing Docker Command:"
# Print the command (quoting the array elements to show how it's executed)
echo "${CMD[@]}"
echo "---------------------------------------------------"

# Execute the command
"${CMD[@]}"