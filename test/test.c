#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#include "priority_queue.h"

static int
cmp_int(const void *aa, const void *bb) {
  int a = *(int *)aa, b = *(int *)bb;
  if (a > b) return  1;
  if (a < b) return -1;
  return 0;
}

static int
test_min_and_max() {
  priority_queue *q1 = priority_queue_create(
    sizeof(int), sizeof(int64_t), cmp_int, priority_queue_min);
  priority_queue *q2 = priority_queue_create(
    sizeof(int), sizeof(int64_t), cmp_int, priority_queue_max);
  int64_t val = 100;
  for (int i=0; i<100; i++) {
    for (int i=1; i<=100; i++) {
      priority_queue_push(q1, &i, &val);
      priority_queue_push(q2, &i, &val);
    }
    for (int i=100; i>0; i--) {
      priority_queue_push(q1, &i, &val);
      priority_queue_push(q2, &i, &val);
    }
  }

  int key = -1;
  val = -1;
  int count[2] = {0};
  int64_t count_val[2] = {0};
  if (priority_queue_peek(q1, &key, NULL))
    if (key != 1)
      return 1;

  if (priority_queue_peek(q2, &key, NULL))
    if (key != 100)
      return 1;

  for (priority_queue_id id; (id = priority_queue_pop(q1, &key, &val));)
    count[0] += key, count_val[0] += val;

  for (priority_queue_id id; (id = priority_queue_pop(q2, &key, &val));)
    count[1] += key, count_val[1] += val;
  printf("%i %"PRIi64"\n%i %"PRIi64"\n", count[0], count_val[0], count[1], count_val[1]);
  priority_queue_destroy(q1);
  priority_queue_destroy(q2);
  if (count[0] == count[1] && count_val[0] == count_val[1])
    return 0;
  return 1;
}


static int
test_random() {
  priority_queue *q1 = priority_queue_create(
    sizeof(int), 0, cmp_int, priority_queue_min);
  priority_queue *q2 = priority_queue_create(
    sizeof(int), 0, cmp_int, priority_queue_max);
  srand(time(NULL));
  int64_t count[3] = {0};
  int val;
  for (int i=0; i<100000; i++) {
    val = rand() & INT32_MAX;
    count[0] += val;
    priority_queue_push(q1, &val, NULL);
    priority_queue_push(q2, &val, NULL);
  }
  while (priority_queue_pop(q1, &val, 0)) count[1] += val;
  while (priority_queue_pop(q2, &val, 0)) count[2] += val;
  printf("%"PRIi64"\n" "%"PRIi64"\n" "%"PRIi64"\n", count[0], count[1], count[2]);
  priority_queue_destroy(q1);
  priority_queue_destroy(q2);
  if (count[0] == count[1] && count[0] == count[2])
    return 0;
  return 1;
}


static int
test_ordering() {
  priority_queue *q1 = priority_queue_create(
    sizeof(int), 0, cmp_int, priority_queue_min);
  priority_queue *q2 = priority_queue_create(
    sizeof(int), 0, cmp_int, priority_queue_max);

  srand(time(NULL));
  int val, last;
  for (int i=0; i<100000; i++) {
    val = rand();
    priority_queue_push(q1, &val, NULL);
    priority_queue_push(q2, &val, NULL);
  }

  priority_queue_pop(q1, &last, 0);
  while (priority_queue_pop(q1, &val, 0)) {
    if (last > val)
      return 1;
    last = val;
  }

  priority_queue_pop(q2, &last, 0);
  while (priority_queue_pop(q2, &val, 0)) {
    if (last < val)
      return 1;
    last = val;
  }
  priority_queue_destroy(q1);
  priority_queue_destroy(q2);
  return 0;
}

int main(int argc, char *argv[]) {
  if (strcmp("min_and_max", argv[1]) == 0)
    return test_min_and_max();
  
  if (strcmp("random", argv[1]) == 0)
    return test_random();

  if (strcmp("ordering", argv[1]) == 0)
    return test_ordering();
}
