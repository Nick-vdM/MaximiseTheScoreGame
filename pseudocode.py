class priority queue<type>:
    public:
        priority queue(inputData<type>):
            for val in inputData:
                data.append
        insert()
        getTop()
        deleteTop()
    private:
        vector<type*> data
        getLeftChild(parentIndex):
        getRightChild(parentIndex)
        getParent(childIndex)
        getMaxChild(parentIndex):
            left = getLeftChild(parentIndex)
            right = getRightChild(parentIndex)
            // recursively search for largest non-zero
            if(left < data.size and *data[left] == 0):
                left = getMaxChild(left)
            if(right < data.size and *data[right] == 0):
                right = getMaxChild(right)

            // since we cannot gaurentee the position of children
            // e.g. right can actually be behind left
            // we have to check if both exist
            if(right >= data.size):
                return left
            if(left >= data.size):
                return right
            // now we know both exist, return the larger of them
            if(*data[left] > *data[right]):
                return left
            return right
        getMaxNode():
            if(*data[0] == 0):
                return getMaxChild(0)
            return 0

        floatUp(index):
            parent = getParent(index)
            while(parent >= 0):
                if(*data[index] > *data[parent]):
                    swap(data[index], data[parent])
                else:
                    stop searching
                index = parent
                parent = getParent(index)
        floatDown(index)
            maxChild = getMaxChild(index)
            while(maxChild < data.size):
                if(*data[index] < *data[maxChildIndex]):
                    swap(data[index], data[maxChildIndex])
                index = maxChild
                maxChild = getMaxChild(index)


####################################################



