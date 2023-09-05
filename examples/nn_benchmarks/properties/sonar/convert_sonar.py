import csv

delta = 0.00001

# Open the CSV file
with open('sonar.csv', 'r') as file:
    # Create a CSV reader object
    reader = csv.reader(file)

    j = 1
    for i, row in enumerate(reader, start=1):
        # if (1 <= i <= 5) or (98 <= i <= 102):
        if i >= 0:
            with open(f'sonar_{j}_{row[-1]}.in', 'w') as target:
                j += 1
                target.write("120 60\n")
                for k in range(len(row[:-1])):
                    line_negative = ['0'] * k + ['-1'] + ['0'] * (59 - k)
                    line_positive = ['0'] * k + ['+1'] + ['0'] * (59 - k)
                    target.write(' '.join(line_negative) + '\n')
                    target.write(' '.join(line_positive) + '\n')

                for k in range(len(row[:-1])):
                    target.write(str((-1 * float(row[k])) + delta) + "\n")
                    target.write(str((+1 * float(row[k])) + delta) + "\n")
