#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/time.h>

#include "sumutils.h"
#include "parsum.h"

#include <pthread.h>

void *ThreadSum(void *args) 
{
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv) 
{

  uint32_t threads_num = -1;
  uint32_t array_size = -1;
  uint32_t seed = -1;

  while (true) 
  {
  	int current_optind = optind ? optind : 1;
	
	static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"threads_num", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);

    if (c == -1)
    	break;

    switch (c) 
    {
      case 0:
        switch (option_index) 
        {
          case 0:
            seed = atoi(optarg);
            // your code here
            if (seed <= 0)
            {
            	printf("seed should be positive!\n\n");
		return 1;
            }
            // error handling
            break;
          case 1:
            array_size = atoi(optarg);
            // your code here
	    if (array_size <= 0)
            {
		printf("array_size should be positive!\n\n");
		return 1;
            }
            // error handling
            break;
          case 2:
            threads_num = atoi(optarg);
            // your code here
	    if (threads_num <= 0)
            {
		printf("threads_num should be positive!\n\n");
		return 1;
            }
            // error handling
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) 
  {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || threads_num == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --threads_num \"num\" \n",
           argv[0]);
    return 1;
  }


  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);

  pthread_t threads[threads_num];
  struct SumArgs args[threads_num];

  int SumSegment = array_size/threads_num;

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

  for (uint32_t i = 0; i < threads_num; i++) 
  {
    args[i].array = array;
    args[i].begin = SumSegment*(i);
    if (i != threads_num - 1)
        args[i].end = SumSegment*(i+1);
    else
        args[i].end = array_size;
  
  if (pthread_create(&threads[i], NULL, ThreadSum, (void *)(args+i))) 
    {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    total_sum += sum;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);
  printf("Total: %d\n", total_sum);
  printf("Elapsed time: %fms\n", elapsed_time);
  return 0;
}