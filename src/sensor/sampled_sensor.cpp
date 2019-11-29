#include "sensor/sampled_sensor.h"

void SampledSensor::add(float value)
{
    samples[insert_index] = value;

    insert_index++;

    if (insert_index >= number_of_samples)
    {
        insert_index = 0;
    }

    if (added_count < number_of_samples)
    {
        added_count++;
    }
}

float SampledSensor::mean()
{
    float sum = 0;

    for (int i = 0; i < added_count; i++)
    {
        sum += samples[i];
    }

    return sum / added_count;
}

float SampledSensor::stddev()
{
    float avg = mean();
    float total = 0.0;

    for (int i = 0; i < added_count; i++)
    {
        total += pow(samples[i] - avg, 2);
    }
    return sqrt(total / (float)added_count - 1.0);
}

void SampledSensor::bubble_sort(float sorted[])
{
    unsigned long new_n;
    unsigned long n = added_count;
    float temp = 0.0;

    for (int i = 0; i < added_count; i++)
    {
        sorted[i] = samples[i];
    }

    do
    {
        new_n = 1;
        for (int p = 1; p < added_count; p++)
        {
            if (sorted[p - 1] > sorted[p])
            {
                temp = sorted[p];
                sorted[p] = sorted[p - 1];
                sorted[p - 1] = temp;

                new_n = p;
            }
        }
        n = new_n;
    } while (n > 1);
}

float SampledSensor::median()
{
    float sorted[added_count];
    bubble_sort(sorted);

    if (added_count % 2 != 0)
    {
        return sorted[added_count / 2];
    }
    else
    {
        return (sorted[(added_count / 2) - 1] + sorted[added_count / 2]) / 2;
    }
}