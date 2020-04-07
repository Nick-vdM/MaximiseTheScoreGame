class priority queue<type>:
    public:
    priority queue(inputData<type>):
        for val in inputData:
            data.append(&val)
        for data.size / 2 - 1 to 0:
            floatDown(i)

    insert(val)
        data.append(&val)
        floatUp(data.size - 1)
    getTop()
        if empty(data) return 0 // this won't affect anything outside
        top = getMaxNode
        return *data[top]
    deleteTop()
        if empty(data) do nothing // nothing to delete
        top = getMaxNode
        // set the inside to 0 so the other player knows
        // that it was picked
        *data[top] = 0
        // normal algorithm: move bottom to the top, erase the bottom
        // and floatdown the top
        data[0] = data[data.size() - 1]
        delete data[data.size - 1]
        floatDown(0)

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

class rustysBall:
    public:
rustysBall(val):
    value = &val
    sumOfDigtis = getSumOfDigits(val)

= operator(other):
    *value = other
    sumOfDigits = sumOfDigits(other)

() operator():
    return *value // only return its value as if its an int

< operator(ball1, ball2):
    // return true if ball1 < ball2 2
    if(ball1.sumOfDigits < ball2.sumOfDigits):
        return true
    if(ball1.sumOfDigits > ball2.sumOfDigits):
        return false
    // in the case that they are equal:
    return *ball1.value < ball2.value

> operator(other):
    // just the inverted version of the above
    // return true if ball1 < ball2 2
    if(ball1.sumOfDigits > ball2.sumOfDigits):
        return true
    if(ball1.sumOfDigits < ball2.sumOfDigits):
        return false
    // in the case that they are equal:
    return *ball1.value > ball2.value

== operator(int other):
    // we only bother comparing the actual value:
    return *r1.value == other

private:
int * value
        int sumOfDigits

getSumOfDigits(val):
    sum = 0
    while (val != 0):
        sum += val % 10
        val /= 10
    return sum



match(vector<int> balls, int maxTurnsPerRound, bool scottsTurn):
    priorityQueue<int> scottsPriorities(balls);
    // calls the rustyBalls constructor on each element and inserts them into
    // a new vector
    auto rustysBalls = turnIntVectorToRustyBallVector(balls);
    priorityQueue<rustysBall> rustysPriorities(rustysBalls);
    int totalTurnsTaken = 0, scottsScore = 0, rustysScore = 0
    while(turnsTaken < balls.size):
        for i in 0 to maxTurnsPerRound and turnsTaken < balls.size:
            if(scottsTurn):
                scottsScore += scottsPriorities.getTop()
                scottsPriorities.deleteTop()
            else:
                rustysScore += rustysPriorities.getTop()
                rustysPriorities.deleteTop()
            turnsTaken++
        scottsTurn != scottsTurn // flip flop the turns each for loop


