#include<iostream>
#include <map>
#include<cstring>
using namespace std;
# define slot
# define siginal protected
# define emit

class Object;

struct MetaObject//元对象 每个Object有一个，保存自己拥有的信号和槽函数
{
	const char* sig_names;
	const char* slts_names;
	static void active(Object* sender, int idx);
};

struct Connection//保存接收方及其序号
{
	Object* receiver;
	int method;
};

typedef std::multimap<int, Connection> ConnectionMap;
//<信号，接收方>每个Object有一个，保存自己的信号发出时需要通知的接收方。每个信号的接收方可能不止一个，用multimap
typedef std::multimap<int, Connection>::iterator ConnectionMapIt;

static int find_string(const char* str, const char* substr)
{
	if (strlen(str) < strlen(substr))
		return -1;
	int idx = 0;
	int len = strlen(substr);
	bool start = true;           //str用\n分隔为一组字符串数组，start用于标识\n之后的有效字符串
	const char* pos = str;
	while (*pos)
	{
		if (start && !strncmp(pos, substr, len) && pos[len] == '\n')
			return idx;
		start = false;
		if (*pos == '\n')
		{
			idx++;
			start = true;
		}
		pos++;
	}
	return -1;
}

class Object
{
	friend class MetaObject;
public:
	Object() {};
	virtual ~Object() {};
	static void connect(Object*sender, const char*sig, Object*receiver, const char*slt);
	void testSignal() { emit sig1(); }//测试函数

siginal:
	void sig1() //信号
	{
		cout << "信号发出" << endl;
		MetaObject::active(this, 0);
	}

public slot:
	void slot1() { cout << "槽函数执行" << endl; }//槽函数
	void slot2() { cout << "槽函数2执行" << endl; }//槽函数

private:
	static MetaObject meta;//保存自己拥有的信号和槽函数
	ConnectionMap connections;//multimap<int, Connection>，
	void metacall(int idx);//根据key去查询对应的槽函数
};

static const char sig_names[] = "sig1\n";//保存对象中所有信号的字符串的容器
// static const char slts_names[] = "slot1\n";//保存对象中所有槽函数字符串的容器
static const char slts_names[] = "slot1\nslot2\n";//保存对象中所有槽函数字符串的容器
MetaObject Object::meta = { sig_names, slts_names };//初始化元对象


void Object::metacall(int idx)//根据key去查询对应的槽函数
{
	switch (idx)
	{
	case 0:
		slot1();
		break;
    case 1:
        slot2();
	default:
		break;
	};
}

void Object::connect(Object*sender, const char*sig, Object*receiver, const char*slt)//静态成员函数  connect建立信号与槽的连接
{
	int sig_idx = find_string(sender->meta.sig_names, sig);//查询有没有这个信号和槽函数
	int slt_idx = find_string(receiver->meta.slts_names, slt);
	if (sig_idx == -1 || slt_idx == -1)
	{
		perror("signal or slot not found!");
	}
	else //添加
	{
		Connection c = { receiver, slt_idx };//保存接收方及其槽函数id
		sender->connections.insert(std::pair<int, Connection>(sig_idx, c));//发送方保存接收方信息
	}
}

void MetaObject::active(Object* sender, int idx)//信号发出，根据发出者找出它的接收方
{
	ConnectionMapIt it;
	std::pair<ConnectionMapIt, ConnectionMapIt> ret;
	ret = sender->connections.equal_range(idx);//equal_range主要是找在multimap中的key相等的value，也是一个迭代器
	for (it = ret.first; it != ret.second; ++it)
	{
		Connection c = (*it).second;//获取之前保存的接受方消息
		c.receiver->metacall(c.method);//接收方执行之前绑定的槽函数
	}
}

int main()
{
	Object obj1, obj2,obj3;
	Object::connect(&obj1, "sig1", &obj2, "slot1");//连接信号
	Object::connect(&obj1, "sig1", &obj3, "slot2");//一个信号可能连接多个槽函数，用multimap存储
	obj1.testSignal();

	system("pause");
	return 0;
}