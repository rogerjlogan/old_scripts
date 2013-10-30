import sys

def main():
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:exit()
    print '\n\n'

    infile = open(args[0], 'r')
    content = infile.read()
    infile.close()
    
    for i in range(63,-1,-1):
        if i<32:
            content = content.replace('bit_arr['+str(i)+']', 'lower['+str(i+1)+']')
            content = content.replace('bit_arr[ '+str(i)+']', 'lower[ '+str(i+1)+']')
        else:
            content = content.replace('bit_arr['+str(i)+']', 'upper['+str(i+1-32)+']')
    
    outfile = open('temp1.txt', 'w')
    outfile.write(content)
    outfile.close()
    
if __name__ == '__main__':
    main()
