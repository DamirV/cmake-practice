#include "pch.h"
#include "..\MyCustomQueue\CustomQueue.h"

TEST(CustomQueue, CanCreate) {
	CustomQueue<int> queue1;
	CustomQueue<int> queue2(10);
    
	EXPECT_EQ(queue1.getSize(), queue2.getSize());
}

TEST(CustomQueue, SizeTest) {
	CustomQueue<int> queue;
	EXPECT_EQ(0, queue.getSize());
	EXPECT_EQ(true, queue.isEmpty());
}

TEST(CustomQueue, CapacityTest) {
	CustomQueue<int> queue1;
	CustomQueue<int> queue2(10);
	EXPECT_EQ(16, queue1.getCapacity());
	EXPECT_EQ(10, queue2.getCapacity());
}

TEST(CustomQueue, PushTest) {
	CustomQueue<int> queue(10);
	
	for (int i = 0; i < 10; ++i) {
		EXPECT_EQ(i, queue.getSize());
		EXPECT_TRUE(queue.push(i));
	}

	EXPECT_TRUE(queue.isFull());
	EXPECT_FALSE(queue.push(11));
}

TEST(CustomQueue, PopTest) {
	CustomQueue<int> queue(10);

	for (int i = 0; i < 10; ++i) {
		EXPECT_TRUE(queue.push(i));
	}

	for (int i = 0; i < 10; ++i) {
		EXPECT_EQ(i, queue.pop());
		EXPECT_EQ(9 - i, queue.getSize());
	}

	EXPECT_EQ(NULL, queue.pop());
}

TEST(CustomQueue, PeekTest) {
	CustomQueue<int> queue(10);

	for (int i = 0; i < 3; ++i) {
		EXPECT_TRUE(queue.push(i));
	}

	EXPECT_EQ(0, queue.peek());
}


TEST(CustomQueue, CpyTest1) {
	CustomQueue<int> queue1(10);

	for (int i = 0; i < 10; ++i) {
		queue1.push(i);
	}

	CustomQueue<int> queue2(queue1);

	EXPECT_EQ(10, queue2.getSize());
	EXPECT_EQ(10, queue2.getCapacity());

	for (int i = 0; i < 10; ++i) {
		EXPECT_EQ(i, queue2.pop());
	}
	
}

TEST(CustomQueue, CpyTest2) {
	CustomQueue<int> queue1(10);

	for (int i = 0; i < 10; ++i) {
		queue1.push(i);
	}

	CustomQueue<int> queue2 = queue1;

	EXPECT_EQ(10, queue2.getSize());
	EXPECT_EQ(10, queue2.getCapacity());

	for (int i = 0; i < 10; ++i) {
		EXPECT_EQ(i, queue2.pop());
	}
}

TEST(CustomQueue, CpyTest3) {
	CustomQueue<int> queue1(10);

	for (int i = 0; i < 10; ++i) {
		queue1.push(i);
	}

	CustomQueue<int> queue2(20);

	for (int i = 0; i < 10; ++i) {
		queue2.push(i);
	}

	queue2 = queue1;

	EXPECT_EQ(10, queue2.getSize());
	EXPECT_EQ(10, queue2.getCapacity());

	for (int i = 0; i < 10; ++i) {
		EXPECT_EQ(i, queue2.pop());
	}
}

TEST(CustomQueue, MoveTest1) {
	CustomQueue<int> queue1(10);

	for (int i = 0; i < 10; ++i) {
		queue1.push(i);
	}

	CustomQueue<int> queue2(std::move(queue1));

	EXPECT_EQ(0, queue1.getSize());
	EXPECT_EQ(16, queue1.getCapacity());

	EXPECT_EQ(10, queue2.getCapacity());
	for (int i = 0; i < 10; ++i) {
		EXPECT_EQ(i, queue2.pop());
		EXPECT_EQ(9 - i, queue2.getSize());
	}
}

TEST(CustomQueue, MoveTest2) {
	CustomQueue<int> queue1(10);

	for (int i = 0; i < 10; ++i) {
		queue1.push(i);
	}

	CustomQueue<int> queue2(20);
	for (int i = 0; i < 10; ++i) {
		queue1.push(i + 10);
	}

	queue2 = std::move(queue1);

	EXPECT_EQ(0, queue1.getSize());
	EXPECT_EQ(16, queue1.getCapacity());

	EXPECT_EQ(10, queue2.getCapacity());
	for (int i = 0; i < 10; ++i) {
		EXPECT_EQ(i, queue2.pop());
		EXPECT_EQ(9 - i, queue2.getSize());
	}
}

TEST(CustomQueue, StressTest) {
	CustomQueue<int> queue(10);

	for (int i = 0; i < 10; ++i) {
		EXPECT_TRUE(queue.push(i));
	}

	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(i, queue.pop());
	}

	for (int i = 10; i < 15; ++i) {
		EXPECT_TRUE(queue.push(i));
	}

	EXPECT_TRUE(queue.isFull());

	for (int i = 5; i < 15; ++i) {
		EXPECT_EQ(i, queue.pop());
	}

	EXPECT_TRUE(queue.isEmpty());
}

