GREEN="\033[32m";
RED="\033[31m";
DEFAULT="\033[37m";
CYAN="\x1b[36m";

MAP_INVALID="maps/invalid/";
MAP_VALID="maps/valid/";
FOLDER="ants/";
FOLDER1="links/";
FOLDER2="rooms/";



P="./lem-in";

# norminette -RCheckForbiddenSourceHeader;
# cat -e author

echo "		\033[31mTESTING INVALID INPUT \033[37m\n"

echo "			\x1b[36mANTS \033[37m"
for file in maps/invalid/ants/*
do
  ./lem-in -v "$file"
done

echo "\x1b[36m ROOMS \033[37m"
for file in maps/invalid/rooms/*
do
  ./lem-in -v "$file"
done

echo "\x1b[36m LINKS \033[37m"
for file in maps/invalid/links/*
do
  ./lem-in -v "$file"
done

echo "\x1b[36m MAP \033[37m"
for file in maps/invalid/map/*
do
  ./lem-in -v "$file"
done

