#include "classes.h"
#include "AccessKey.h"

void Observable::Attach(Observer& observer)
{
    observerSet_.insert(&observer);
}

void Observable::Detach(Observer& observer)
{
    observerSet_.erase(&observer);
}

void Observable::Notify(const void* dataKey)
{
    for (auto& observer : observerSet_)
    {
        observer->Update(*this, dataKey);
    }
}

Observable::~Observable() = default;


ChatRoom::ChatRoom(std::string name)
    : name_(std::move(name))
{}

void ChatRoom::SendMessage(std::string const& message)
{
    Notify(&message);
}

std::string ChatRoom::GetName() const 
{ 
    return name_; 
}

std::string const& ChatRoom::GetDataFromKey(design::AccessKey<Observer>, const void* dataKey)
{
    assert(dataKey);
    return *reinterpret_cast<std::string const*>(dataKey);
}

User::User(std::string name)
    : name_(std::move(name))
{}

void User::Update(Observable& observable, const void* dataKey)
{
    auto& chatRoom = static_cast<ChatRoom&>(observable);
    assert(chatRoomSet_.find(&chatRoom) != std::end(chatRoomSet_));

    std::cout << "[" << name_ << "][" << chatRoom.GetName() << "] " <<
        chatRoom.GetDataFromKey(GetAccessKey(), dataKey) << std::endl;
}

void User::JoinChatRoom(ChatRoom& chatRoom)
{
    chatRoomSet_.insert(&chatRoom);
    chatRoom.Attach(*this);
}
int main()
{
    ChatRoom chatRoom_1("ChatRoom_1"), chatRoom_2("ChatRoom_2");
    User user_1("User_1"), user_2("User_2"), user_3("User_3");

    user_1.JoinChatRoom(chatRoom_1);
    user_2.JoinChatRoom(chatRoom_2);
    user_3.JoinChatRoom(chatRoom_1);
    user_3.JoinChatRoom(chatRoom_2);

    chatRoom_1.SendMessage("Hi, nice to meet you!");
    chatRoom_2.SendMessage("I'm Taeguk Kwon!");
}