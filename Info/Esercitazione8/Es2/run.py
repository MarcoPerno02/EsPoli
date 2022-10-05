def neighbor_average(values, row, column):
    media = 0
    count = 0
    for i in range(row-1, row+2):
        for j in range(column-1,  column+2):
            if(i>=0 and j>=0 and i<len(values) and j<len(values[0]) and (i!=row or j!=column)):
                media+=values[i][j]
                count+=1
    media/=count
    return media

values = [[1, 2, 3],
          [4, 5, 6],
          [7, 8, 9]]
print(neighbor_average(values, 2, 2))
