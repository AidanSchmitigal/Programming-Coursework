# Upload all files to a folder on a remote server and run make then display the output of make
# Usage: testFlip.sh <uploadFolder> <uploadServer> <uploadDestination> <sshKey>

# Check for correct number of arguments
if [ $# -ne 4 ]; then
    echo "Usage: testFlip.sh <uploadFolder> <uploadServer> <uploadDestination> <sshKey>"
    exit 1
fi

# Check for valid upload folder
if [ ! -d $1 ]; then
    echo "Error: $1 is not a valid folder"
    exit 1
fi

# Check for valid upload server
if [ ! -f $4 ]; then
    echo "Error: $4 is not a valid ssh key"
    exit 1
fi

# Define color escape codes
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

# Upload files to remote server
echo "Uploading files to $2"
echo ${CYAN}
scp -i $4 -r $1 $2:$3
echo ${NC}

# Run make on remote server
echo "Running make on $2"
echo ${GREEN}
ssh -i $4 $2 "cd $3/$1; make"
echo ${NC}