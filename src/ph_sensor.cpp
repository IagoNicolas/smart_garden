#include "ph_sensor.h"
#include <Arduino.h>

/**
 * @brief Size of the buffer used for collecting pH readings.
 */
const int BUFFER_SIZE = 10;

/**
 * @brief Delay in milliseconds between consecutive pH readings.
 */
const int DELAY_MS = 30;

/**
 * @brief Lower bound index for selecting readings within the buffer.
 */
const int LOWER_BOUND = 2;

/**
 * @brief Upper bound index for selecting readings within the buffer.
 */
const int UPPER_BOUND = 8;

/**
 * @brief Analog port to which the pH sensor is connected.
 */
const uint8_t PH_READING_PORT = A0;

/**
 * @brief Calibration value for converting voltage to pH.
 */
const float CALIBRATION_VALUE = 10.34;

/**
 * @brief Perform bubble sort on an array.
 *
 * @param arr The array to be sorted.
 * @param n   The size of the array.
 */
void bubbleSort(uint32_t arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // swap arr[j] and arr[j + 1]
                uint32_t temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Get the pH value from the connected pH sensor.
 *
 * This function collects a series of pH readings, sorts them, calculates
 * the average within specified bounds, converts the average voltage to pH,
 * and returns the pH value.
 *
 * @return The pH value.
 */
double getPhValue() {
    uint32_t bufferArray[BUFFER_SIZE];
    unsigned long int averageReadings = 0;

    // Collect readings into the buffer
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        bufferArray[i] = analogRead(PH_READING_PORT);
        delay(DELAY_MS);
    }

    // Sort the buffer in ascending order using bubble sort
    bubbleSort(bufferArray, BUFFER_SIZE);

    // Calculate the average of readings within the specified bounds
    for (int i = LOWER_BOUND; i < UPPER_BOUND; ++i) {
        averageReadings += bufferArray[i];
    }

    // Calculate voltage and convert to pH
    double volt = static_cast<double>(averageReadings) * 5.0 / 1024 / (UPPER_BOUND - LOWER_BOUND);
    double phConverted = -5.70 * volt + CALIBRATION_VALUE;

    return phConverted;
}
