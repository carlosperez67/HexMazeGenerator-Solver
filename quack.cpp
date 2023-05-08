/**
 * @file quack.cpp
 * Implementation of the Quack class.
 *
 */

template <class T>
Quack<T>::Quack() {
    /**
     * @todo Your code here!
     */


    n1 = 0;
    n2 = -1;              // init value so when we add first element we will get zero
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */
template <class T>
void Quack<T>::pushR(T newItem) {
    /**
     * @todo Your code here!
     */

    data.push_back(newItem);
    n2++;                     // because we added one element
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */
template <class T>
T Quack<T>::popL() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */

    T result = data.at(n1);
    n1++;

    int emptyPositionsFront = n1;
    int totalPositionsUsed = n2 + 1 - n1;

    // Performing the Resize down and changing the other fields
    if (emptyPositionsFront >= totalPositionsUsed) {
        /**
        * @todo Resize down and create a new vector
        */
       vector<T> newVector;

       for (int i = n1; i <= n2 && n1 <= n2; i++) {
            newVector.push_back(data.at(i));
       }
       data = newVector;
       n1 = 0;
       n2 = totalPositionsUsed - 1;
    }
    return result;
}




/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::popR() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    T result = data.back();
    data.pop_back();
    n2--;

    int emptyPositionsFront = n1;
    int totalPositionsUsed = n2 + 1 - n1;

    // Performing the Resize down and changing the other fields
    if (emptyPositionsFront >= totalPositionsUsed) {
        /**
        * @todo Resize down and create a new vector
        */
       vector<T> newVector;

       for (int i = n1; i <= n2 && n1 <= n2; i++) {
            newVector.push_back(data.at(i));
       }
       data = newVector;
       n1 = 0;
       n2 = totalPositionsUsed - 1 ;
    }

    return result;
}


/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike popL(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return data.at(n1);
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike popR(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return data.at(n2);
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::isEmpty() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    int totalPositionsUsed = n2 + 1 - n1;
    if (data.empty() || n2 < n1) 
        return true;
    else
        return false;
}
