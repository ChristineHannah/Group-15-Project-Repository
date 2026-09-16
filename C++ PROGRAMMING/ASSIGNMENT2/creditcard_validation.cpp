#include <iostream>

// Function prototypes as specified in the instructions
bool isValid(long long number);
int sumOfDoubleEvenPlace(long long number);
int getDigit(int number);
int sumOfOddPlace(long long number);
bool prefixMatched(long long number, int d);
int getSize(long long d);
long long getPrefix(long long number, int k);

int main() {
    long long cardNumber;
    std::cout << "Enter a credit card number as an integer: ";
    std::cin >> cardNumber;

    if (isValid(cardNumber)) {
        std::cout << cardNumber << " is valid" << std::endl;
    } else {
        std::cout << cardNumber << " is invalid" << std::endl;
    }

    return 0;
}

// Return true if the card number is valid
bool isValid(long long number) {
    int totalSize = getSize(number);
    
    // Check length constraint (between 13 and 16 digits)
    if (totalSize < 13 || totalSize > 16) {
        return false;
    }
    
    // Check prefix patterns (4 for Visa, 5 for MasterCard, 37 for AMEX, 6 for Discover)
    if (!prefixMatched(number, 4) && 
        !prefixMatched(number, 5) && 
        !prefixMatched(number, 37) && 
        !prefixMatched(number, 6)) {
        return false;
    }
    
    // Perform Luhn's totals and check if sum is divisible by 10
    int finalSum = sumOfDoubleEvenPlace(number) + sumOfOddPlace(number);
    return (finalSum % 10 == 0);
}

// Get the result from Step 2 (Double every second digit from right to left)
int sumOfDoubleEvenPlace(long long number) {
    int sum = 0;
    number /= 10; // Shift to start at the second digit from the right (even place)
    
    while (number > 0) {
        int lastDigit = number % 10;
        sum += getDigit(lastDigit * 2);
        number /= 100; // Skip next odd place digit to get to the next even place
    }
    return sum;
}

// Return this number if it is a single digit, otherwise, return the sum of the two digits
int getDigit(int number) {
    if (number < 10) {
        return number;
    }
    return (number / 10) + (number % 10);
}

// Return sum of odd place digits in number from right to left
int sumOfOddPlace(long long number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 100; // Move up two decimal places to jump to the next odd place
    }
    return sum;
}

// Return true if the digit d is a prefix for number
bool prefixMatched(long long number, int d) {
    int dSize = getSize(d);
    return getPrefix(number, dSize) == d;
}

// Return the number of digits in d
int getSize(long long d) {
    int count = 0;
    if (d == 0) return 1;
    while (d > 0) {
        count++;
        d /= 10;
    }
    return count;
}

// Return the first k number of digits from number.
// If the number of digits in number is less than k, return number.
long long getPrefix(long long number, int k) {
    int size = getSize(number);
    if (size < k) {
        return number;
    }
    
    int digitsToRemove = size - k;
    for (int i = 0; i < digitsToRemove; i++) {
        number /= 10;
    }
    return number;
}
