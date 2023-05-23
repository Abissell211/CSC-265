void shuffle(char *array, size_t n) {    
// obtained from https://stackoverflow.com/questions/6127503/shuffle-array-in-c
    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            char t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
	int j = rand() % n;
	char t = array[j];
        array[j] = array[0];
        array[0] = t;

    }
}
