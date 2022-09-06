import sys
import csv

# Loop through sequence


def count_str(str, sequence):
    max_count = 0
    count = 0
    while True:
        ix = sequence.find(str)
        if ix == -1:
            break
        if ix != 0 and count != 0:
            count = 0
        sequence = sequence[ix + len(str):]
        count += 1
        if count > max_count:
            max_count = count
    return max_count


def is_equal(seq, user, fieldnames):
    for i in range(1, len(fieldnames)):
        fn = fieldnames[i]
        if seq[fn] != int(user[fn]):
            return False
    return True


if len(sys.argv) != 3:
    print("missing command-line argument")
    sys.exit(0)

# Read csv file
file = open(sys.argv[1], "r")
reader = csv.DictReader(file)
fieldnames = reader.fieldnames

# Read sequence file
f = open(sys.argv[2], "r")
sequence = f.read()

f.close()

dict_fieldnames = {}
for i in range(1, len(fieldnames)):
    total = count_str(fieldnames[i], sequence)
    dict_fieldnames[fieldnames[i]] = total

flag = False
for row in reader:
    if is_equal(dict_fieldnames, row, fieldnames):
        flag = True
        print(row["name"])
        break
if flag == False:
    print("No match")
