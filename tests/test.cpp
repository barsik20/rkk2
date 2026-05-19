#include <gtest/gtest.h>
#include "../AccessKey.h"
#include "../classes.h"

class room: public testing::Test {
public:
	ChatRoom* cr;
	void SetUp() { cr = new ChatRoom("adddddsssss"); }
	void TearDown() { delete cr; }
};

TEST_F(room, GetDataFromKey) {
	EXPECT_EQ(cr->GetName(), "adddddsssss");
}