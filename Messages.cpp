#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include "Messages.h"

RobotOrder::RobotOrder() {
	customer_id = -1;
	order_number = -1;
	request_type = -1;
}

void RobotOrder::SetOrder(int id, int number, int type) {
	customer_id = id;
	order_number = number;
	request_type = type;
}

int RobotOrder::GetCustomerId() { return customer_id; }
int RobotOrder::GetOrderNumber() { return order_number; }
int RobotOrder::GetRobotType() { return request_type; }

int RobotOrder::Size() {
	return sizeof(customer_id) + sizeof(order_number) + sizeof(request_type);
}

void RobotOrder::Marshal(char *buffer) {
	int net_customer_id = htonl(customer_id);
	int net_order_number = htonl(order_number);
	int net_request_type = htonl(request_type);
	int offset = 0;
	memcpy(buffer + offset, &net_customer_id, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(buffer + offset, &net_order_number, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(buffer + offset, &net_request_type, sizeof(net_request_type));
}

void RobotOrder::Unmarshal(char *buffer) {
	int net_customer_id;
	int net_order_number;
	int net_request_type;
	int offset = 0;
	memcpy(&net_customer_id, buffer + offset, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(&net_order_number, buffer + offset, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(&net_request_type, buffer + offset, sizeof(net_request_type));

	customer_id = ntohl(net_customer_id);
	order_number = ntohl(net_order_number);
	request_type = ntohl(net_request_type);
}

bool RobotOrder::IsValid() {
	return (customer_id != -1);
}

void RobotOrder::Print() {
	std::cout << "id " << customer_id << " ";
	std::cout << "num " << order_number << " ";
	std::cout << "type " << request_type << std::endl;
}

RobotInfo::RobotInfo() {
	customer_id = -1;
	order_number = -1;
	request_type = -1;
	engineer_id = -1;
	admin_id = -1;
}

void RobotInfo::SetInfo(int id, int number, int type, int engid, int expid) {
	customer_id = id;
	order_number = number;
	request_type = type;
	engineer_id = engid;
	admin_id = expid;
}

// void RobotInfo::CopyOrder(RobotOrder order) {
// 	customer_id = order.GetCustomerId();
// 	order_number = order.GetOrderNumber();
// 	request_type = order.GetRobotType();
// }
void RobotInfo::CopyRequest(CustomerRequest request) {
	customer_id = request.GetCustomerId();
	order_number = request.GetOrderNumber();
	request_type = request.GetRequestType();
}
void RobotInfo::SetEngineerId(int id) { engineer_id = id; }
void RobotInfo::SetAdminId(int id) { admin_id = id; }

int RobotInfo::GetCustomerId() { return customer_id; }
int RobotInfo::GetOrderNumber() { return order_number; }
//int RobotInfo::GetRobotType() { return request_type; }
int RobotInfo::GetRequestType() { return request_type; }
int RobotInfo::GetEngineerId() { return engineer_id; }
int RobotInfo::GetAdminId() { return admin_id; }

int RobotInfo::Size() {
	return sizeof(customer_id) + sizeof(order_number) + sizeof(request_type)
		+ sizeof(engineer_id) + sizeof(admin_id);
}

void RobotInfo::Marshal(char *buffer) {
	int net_customer_id = htonl(customer_id);
	int net_order_number = htonl(order_number);
	int net_request_type = htonl(request_type);
	int net_engineer_id = htonl(engineer_id);
	int net_admin_id = htonl(admin_id);
	int offset = 0;

	memcpy(buffer + offset, &net_customer_id, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(buffer + offset, &net_order_number, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(buffer + offset, &net_request_type, sizeof(net_request_type));
	offset += sizeof(net_request_type);
	memcpy(buffer + offset, &net_engineer_id, sizeof(net_engineer_id));
	offset += sizeof(net_engineer_id);
	memcpy(buffer + offset, &net_admin_id, sizeof(net_admin_id));

}

void RobotInfo::Unmarshal(char *buffer) {
	int net_customer_id;
	int net_order_number;
	int net_request_type;
	int net_engineer_id;
	int net_admin_id;
	int offset = 0;

	memcpy(&net_customer_id, buffer + offset, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(&net_order_number, buffer + offset, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(&net_request_type, buffer + offset, sizeof(net_request_type));
	offset += sizeof(net_request_type);
	memcpy(&net_engineer_id, buffer + offset, sizeof(net_engineer_id));
	offset += sizeof(net_engineer_id);
	memcpy(&net_admin_id, buffer + offset, sizeof(net_admin_id));

	customer_id = ntohl(net_customer_id);
	order_number = ntohl(net_order_number);
	request_type = ntohl(net_request_type);
	engineer_id = ntohl(net_engineer_id);
	admin_id = ntohl(net_admin_id);
}

bool RobotInfo::IsValid() {
	return (customer_id != -1);
}

void RobotInfo::Print() {
	std::cout << "id " << customer_id << " ";
	std::cout << "num " << order_number << " ";
	std::cout << "type " << request_type << " ";
	std::cout << "engid " << engineer_id << " ";
	std::cout << "expid " << admin_id << std::endl;
}

CustomerRequest::CustomerRequest() {
	customer_id = -1;
	order_number = -1;
	request_type = -1;
}

void CustomerRequest::SetRequest(int id, int number, int type) {
	customer_id = id;
	order_number = number;
	request_type = type;
}

int CustomerRequest::GetCustomerId() { return customer_id; }
int CustomerRequest::GetOrderNumber() { return order_number; }
int CustomerRequest::GetRequestType() { return request_type; }

int CustomerRequest::Size() {
	return sizeof(customer_id) + sizeof(order_number) + sizeof(request_type);
}

void CustomerRequest::Marshal(char *buffer) {
	int net_customer_id = htonl(customer_id);
	int net_order_number = htonl(order_number);
	int net_request_type = htonl(request_type);
	int offset = 0;
	memcpy(buffer + offset, &net_customer_id, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(buffer + offset, &net_order_number, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(buffer + offset, &net_request_type, sizeof(net_request_type));
}

void CustomerRequest::Unmarshal(char *buffer) {
	int net_customer_id;
	int net_order_number;
	int net_request_type;
	int offset = 0;
	memcpy(&net_customer_id, buffer + offset, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(&net_order_number, buffer + offset, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(&net_request_type, buffer + offset, sizeof(net_request_type));

	customer_id = ntohl(net_customer_id);
	order_number = ntohl(net_order_number);
	request_type = ntohl(net_request_type);
}

bool CustomerRequest::IsValid() {
	return (customer_id != -1);
}

void CustomerRequest::Print() {
	std::cout << "id " << customer_id << " ";
	std::cout << "num " << order_number << " ";
	std::cout << "type " << request_type << std::endl;
}

CustomerRecord::CustomerRecord() {
	customer_id = -1;
	last_order = -1;
}

void CustomerRecord::setRecord(int cid, int order_num) {
	customer_id = cid;
	last_order = order_num;
}

void CustomerRecord::setCustomerId(int cid) {
	customer_id = cid;
}

void CustomerRecord::setOrderNumber(int order_num) { last_order = order_num; }

int CustomerRecord::GetCustomerId() { return customer_id; }
int CustomerRecord::GetOrderNumber() { return last_order; }

int CustomerRecord::Size() {
	return sizeof(customer_id) + sizeof(last_order);
}

void CustomerRecord::Marshal(char *buffer) {
	int net_customer_id = htonl(customer_id);
	int net_order_number = htonl(last_order);
	int offset = 0;

	memcpy(buffer + offset, &net_customer_id, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(buffer + offset, &net_order_number, sizeof(net_order_number));
	offset += sizeof(net_order_number);
}

void CustomerRecord::Unmarshal(char *buffer) {
	int net_customer_id;
	int net_order_number;
	int offset = 0;

	memcpy(&net_customer_id, buffer + offset, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(&net_order_number, buffer + offset, sizeof(net_order_number));
	offset += sizeof(net_order_number);

	customer_id = ntohl(net_customer_id);
	last_order = ntohl(net_order_number);
}

bool CustomerRecord::IsValid() {
	return (customer_id != -1);
}

void CustomerRecord::Print() {
	std::cout << "customer_id " << customer_id << "\t";
	std::cout << "last_order " << last_order << std::endl;
}

Protocol::Protocol() {
	last_index = -1;
	commited_index = -1;
	factory_id = -1;
	opcode = -1;
	arg1 = -1;
	arg2 = -1;
}

void Protocol::SetProtocol(int lastIndex, int commitedIndex, int factoryId, int opCode, int argument1, int argument2) {
	last_index = lastIndex;
	commited_index = commitedIndex;
	factory_id = factoryId;
	opcode = opCode;
	arg1 = argument1;
	arg2 = argument2;
}

int Protocol::GetLastIndex() { return last_index; }
int Protocol::GetCommitedIndex() { return commited_index; }
int Protocol::GetFactoryId() { return factory_id; }
int Protocol::GetOpcode() { return opcode; }
int Protocol::GetArg1() { return arg1; }
int Protocol::GetArg2() { return arg2; }

int Protocol::Size() {
	return sizeof(last_index) + sizeof(commited_index) + sizeof(factory_id)
	+ sizeof(opcode) + sizeof(arg1) + sizeof(arg2);
}

void Protocol::Marshal(char *buffer) {
	int net_last_index = htonl(last_index);
	int net_commited_index = htonl(commited_index);
	int net_factory_id = htonl(factory_id);
	int net_opcode = htonl(opcode);
	int net_arg1 = htonl(arg1);
	int net_arg2 = htonl(arg2);
	int offset = 0;

	memcpy(buffer + offset, &net_last_index, sizeof(net_last_index));
	offset += sizeof(net_last_index);
	memcpy(buffer + offset, &net_commited_index, sizeof(net_commited_index));
	offset += sizeof(net_commited_index);
	memcpy(buffer + offset, &net_factory_id, sizeof(net_factory_id));
	offset += sizeof(net_factory_id);
	memcpy(buffer + offset, &net_opcode, sizeof(net_opcode));
	offset += sizeof(net_opcode);
	memcpy(buffer + offset, &net_arg1, sizeof(net_arg1));
	offset += sizeof(net_arg1);
	memcpy(buffer + offset, &net_arg2, sizeof(net_arg2));
}

void Protocol::Unmarshal(char *buffer) {
	int net_last_index;
	int net_commited_index;
	int net_factory_id;
	int net_opcode;
	int net_arg1;
	int net_arg2;
	int offset = 0;

	memcpy(&net_last_index, buffer + offset, sizeof(net_last_index));
	offset += sizeof(net_last_index);
	memcpy(&net_commited_index, buffer + offset, sizeof(net_commited_index));
	offset += sizeof(net_commited_index);
	memcpy(&net_factory_id, buffer + offset, sizeof(net_factory_id));
	offset += sizeof(net_factory_id);
	memcpy(&net_opcode, buffer + offset, sizeof(net_opcode));
	offset += sizeof(net_opcode);
	memcpy(&net_arg1, buffer + offset, sizeof(net_arg1));
	offset += sizeof(net_arg1);
	memcpy(&net_arg2, buffer + offset, sizeof(net_arg2));

	last_index = ntohl(net_last_index);
	commited_index = ntohl(net_commited_index);
	factory_id = ntohl(net_factory_id);
	opcode = ntohl(net_opcode);
	arg1 = ntohl(net_arg1);
	arg2 = ntohl(net_arg2);
}

bool Protocol::IsValid() {
	return (last_index != -1);
}

void Protocol::Print() {
	std::cout << "last_index " << last_index << "\t";
	std::cout << "commited_index " << commited_index << "\t";
	std::cout << "factory_id " << factory_id << "\t";
	std::cout << "opcode " << opcode << "\t";
	std::cout << "argument1 " << arg1 << "\t";
	std::cout << "argument2 " << arg2 << std::endl;
}

Status::Status() {
	statusCode = -1;
}

void Status::SetStatus(int code) {
	statusCode = code;
}

int Status::GetStatusCode() { return statusCode; }

int Status::Size() {
	return sizeof(statusCode);
}

void Status::Marshal(char *buffer) {
	int net_statusCode = htonl(statusCode);
	memcpy(buffer, &net_statusCode, sizeof(net_statusCode));
}

void Status::Unmarshal(char *buffer) {
	int net_statusCode;

	memcpy(&net_statusCode, buffer, sizeof(net_statusCode));

	statusCode = ntohl(net_statusCode);
}

bool Status::IsValid() {
	return (statusCode != -1);
}

void Status::Print() {
	std::cout << "status_code " << statusCode << std::endl;
}

Identity::Identity() {
	identityCode = -1;
}

void Identity::SetIdentity(int code) {
	identityCode = code;
}

int Identity::GetIdentityCode() { return identityCode; }

int Identity::Size() {
	return sizeof(identityCode);
}

void Identity::Marshal(char *buffer) {
	int net_identityCode = htonl(identityCode);
	memcpy(buffer, &net_identityCode, sizeof(net_identityCode));
}

void Identity::Unmarshal(char *buffer) {
	int net_identityCode;

	memcpy(&net_identityCode, buffer, sizeof(net_identityCode));

	identityCode = ntohl(net_identityCode);
}

bool Identity::IsValid() {
	return (identityCode != -1);
}

void Identity::Print() {
	std::cout << "identityCode_code " << identityCode << std::endl;
}
