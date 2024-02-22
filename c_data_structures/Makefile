CC = gcc
CFLAGS = -Wall -g -fsanitize=address -static-libasan
BIN_DIR = bin
SRC_DIR = src

ll_test: LL_Test.c $(SRC_DIR)/linked_list.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) $(SRC_DIR)/linked_list.c -o $(BIN_DIR)/ll.o
	$(CC) $(CFLAGS) LL_Test.c $(BIN_DIR)/ll.o -o $(BIN_DIR)/ll_test
	./$(BIN_DIR)/ll_test

cll_test: CLL_Test.c $(SRC_DIR)/clinked_list.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) $(SRC_DIR)/clinked_list.c -o $(BIN_DIR)/cll.o
	$(CC) $(CFLAGS) CLL_Test.c $(BIN_DIR)/cll.o -o $(BIN_DIR)/cll_test
	./$(BIN_DIR)/cll_test

queue_test: Queue_Test.c $(SRC_DIR)/queue.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) $(SRC_DIR)/queue.c -o $(BIN_DIR)/queue.o
	$(CC) $(CFLAGS) Queue_Test.c $(BIN_DIR)/queue.o -o $(BIN_DIR)/queue_test
	./$(BIN_DIR)/queue_test

bst_test: BST_Test.c $(SRC_DIR)/bstree.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) $(SRC_DIR)/bstree.c -o $(BIN_DIR)/bstree.o
	$(CC) $(CFLAGS) BST_Test.c $(BIN_DIR)/bstree.o -o $(BIN_DIR)/bst_test
	./$(BIN_DIR)/bst_test

hashtable_test: HashTable_Test.c $(SRC_DIR)/hashtable.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) $(SRC_DIR)/hashtable.c -o $(BIN_DIR)/hashtable.o
	$(CC) $(CFLAGS) HashTable_Test.c $(BIN_DIR)/hashtable.o -o $(BIN_DIR)/hashtable_test
	./$(BIN_DIR)/hashtable_test

stack_test: Stack_Test.c $(SRC_DIR)/stack.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) $(SRC_DIR)/stack.c -o $(BIN_DIR)/stack.o
	$(CC) $(CFLAGS) Stack_Test.c $(BIN_DIR)/stack.o -o $(BIN_DIR)/stack_test
	./$(BIN_DIR)/stack_test

graph_test: WeightedGraph_Test.c $(SRC_DIR)/graph.c $(SRC_DIR)/minheap.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) $(SRC_DIR)/graph.c -o $(BIN_DIR)/graph.o
	$(CC) -c $(CFLAGS) $(SRC_DIR)/minheap.c -o $(BIN_DIR)/minheap.o
	$(CC) $(CFLAGS) WeightedGraph_Test.c $(BIN_DIR)/graph.o $(BIN_DIR)/minheap.o -o $(BIN_DIR)/graph_test
	./$(BIN_DIR)/graph_test

pqueue_test: PriorityQueue_Test.c $(SRC_DIR)/pqueue.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) $(SRC_DIR)/pqueue.c -o $(BIN_DIR)/pqueue.o
	$(CC) $(CFLAGS) PriorityQueue_Test.c $(BIN_DIR)/pqueue.o -o $(BIN_DIR)/pqueue_test
	./$(BIN_DIR)/pqueue_test

tpool_test: ThreadPool_Test.c $(SRC_DIR)/tpool.c $(BIN_DIR)/.dirstamp
	$(CC) -c $(CFLAGS) -pthread $(SRC_DIR)/tpool.c -o $(BIN_DIR)/tpool.o
	$(CC) $(CFLAGS) -pthread ThreadPool_Test.c $(BIN_DIR)/tpool.o -o $(BIN_DIR)/tpool_test
	./$(BIN_DIR)/tpool_test

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
