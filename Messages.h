#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>

class RobotOrder {
private:
	int customer_id;
	int order_number;
	int request_type;

public:
	RobotOrder();
	void operator = (const RobotOrder &order) {
		customer_id = order.customer_id;
		order_number = order.order_number;
		request_type = order.request_type;
	}
	void SetOrder(int cid, int order_num, int type);
	int GetCustomerId();
	int GetOrderNumber();
	int GetRobotType();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};

class CustomerRequest {
private:
	int customer_id;
	int order_number;
	int request_type;

public:
	CustomerRequest();
	void operator = (const CustomerRequest &request) {
		customer_id = request.customer_id;
		order_number = request.order_number;
		request_type = request.request_type;
	}
	void SetRequest(int cid, int order_num, int type);
	int GetCustomerId();
	int GetOrderNumber();
	int GetRequestType();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};

class RobotInfo {
private:
	int customer_id;
	int order_number;
	int request_type;
	int engineer_id;
	int admin_id;

public:
	RobotInfo();
	void operator = (const RobotInfo &info) {
		customer_id = info.customer_id;
		order_number = info.order_number;
		request_type = info.request_type;
		engineer_id = info.engineer_id;
		admin_id = info.admin_id;
	}
	void SetInfo(int cid, int order_num, int type, int engid, int expid);
	//void CopyOrder(RobotOrder order);
	void CopyRequest(CustomerRequest request);
	void SetEngineerId(int id);
	void SetAdminId(int id);

	int GetCustomerId();
	int GetOrderNumber();
	//int GetRobotType();
	int GetRequestType();
	int GetEngineerId();
	int GetAdminId();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};

class CustomerRecord {
private:
	int customer_id;
	int last_order;

public:
	CustomerRecord();
	void operator = (const CustomerRecord &record) {
		customer_id = record.customer_id;
		last_order = record.last_order;
	}
	void setRecord(int cid, int order_num);
	void setCustomerId(int cid);
	void setOrderNumber(int order_num);

	int GetCustomerId();
	int GetOrderNumber();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};

class Protocol {
private:
	int last_index;
	int commited_index;
	int factory_id;
	int opcode;
	int arg1;
	int arg2;

public:
	Protocol();
	void operator = (const Protocol &protocol) {
		last_index = protocol.last_index;
		commited_index = protocol.commited_index;
		factory_id = protocol.factory_id;
		opcode = protocol.opcode;
		arg1 = protocol.arg1;
		arg2 = protocol.arg2;
	}

	void SetProtocol(int last_index, int commited_index, int factory_id, int opcode, int arg1, int arg2);

	int GetLastIndex();
	int GetCommitedIndex();
	int GetFactoryId();
	int GetOpcode();
	int GetArg1();
	int GetArg2();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};

class Status {
private:
	int statusCode; // 0 is successful -1 is unsuccessful

public:
	Status();
	void operator = (const Status &status) {
		statusCode = status.statusCode;
	}

	void SetStatus(int statusCode);

	int GetStatusCode();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};

class Identity {
private:
	int identityCode; // 0 is from client 1 is from PFA

public:
	Identity();
	void operator = (const Identity &identity) {
		identityCode = identity.identityCode;
	}

	void SetIdentity(int identityCode);

	int GetIdentityCode();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};



#endif // #ifndef __MESSAGES_H__
