objdump -D $1 | grep -A1 -e "\(malloc\|free\)"  | grep [re]ax | awk -F\: '{ print $1 }'
