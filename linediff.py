import sys

RED = '\033[91m'
PINK = '\033[38;5;206m'
WHITE = '\033[0m'
CEND = '\033[0m'

def finish_stream(stream, line, idx):
	stream += f'{RED}'
	for i in range(idx, len(line)):
		stream += line[i]
	return stream + f'{CEND}'

arg1 = sys.argv[1]
arg2 = sys.argv[2]

f = open(arg1,'r')
g = open(arg2,'r')

idx = 0

stream1 = ''
stream2 = ''

for line1, line2 in zip(f,g):
	for char1, char2 in zip(line1,line2):
		if char1 == char2:
			stream1 += f"{char1}"
			stream2 += f"{char2}"
		else:
			stream1 += f"{RED}{char1}{CEND}"
			stream2 += f"{RED}{char2}{CEND}"
		idx += 1
	# check if streams are done
	if (len(line1) == idx):
		stream2 = finish_stream(stream2, line2, idx)
	if (len(line2) == idx):
		stream1 = finish_stream(stream1, line1, idx)

print(f'{stream1}')
print(f'{stream2}')
