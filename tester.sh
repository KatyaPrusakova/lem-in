GREEN="\033[32m";
RED="\033[31m";
DEFAULT="\033[37m";
CYAN="\x1b[36m";

P="./lem-in";

# norminette -RCheckForbiddenSourceHeader;
# cat -e author

echo "		\033[31mTESTING INVALID INPUT \033[37m\n"

# echo "			\x1b[36mANTS \033[37m"
# for file in maps/invalid/ants/*
# do
# 	 echo "$file"
#   ./lem-in -v "$file"
# 	 echo "\n"
# done

# echo "\x1b[36m ROOMS \033[37m"
# for file in maps/invalid/rooms/*
# do
# 	echo "$file"
#   ./lem-in -v "$file"
#     echo "\n"
# done

# echo "\x1b[36m LINKS \033[37m"
# for file in maps/invalid/links/*
# do
# 	echo "$file"
#   ./lem-in -v "$file"
#     echo "\n"
# done

# echo "\x1b[36m MAP \033[37m"
# for file in maps/invalid/map/*
# do
# 	echo "$file"
#   ./lem-in -v "$file"
#     echo "\n"
# done

# 
echo "		\033[31mTESTING VALID INPUT \033[37m\n"
# 

# echo "\x1b[36m BIG \033[37m"
# for file in maps/valid/big/*
# do
#   ./lem-in -v "$file"
# done

# echo "\x1b[36m SUPER BIG MAP \033[37m"
# for file in maps/valid/big_sup/*
# do
#   ./lem-in -v "$file"
# done

# echo "\x1b[36m SIMPLE MAP \033[37m"
# for file in maps/valid/simple/*
# do
#   ./lem-in -v "$file"
# done