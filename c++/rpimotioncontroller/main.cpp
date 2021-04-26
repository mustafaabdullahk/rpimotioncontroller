#include <QCoreApplication>
#include <QDebug>

#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>
#include <motioncontroller.grpc.pb.h>
#include <motioncontroller.pb.h>
#include <thread>

#include "3rdparty/debug.h"
#include "drivercontext.h"
#include "drivers/ads1256.h"
#include "drivers/dac8532.h"
#include "drivers/gpiodriver.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

void runMyServer(motioncontroller::DeviceService::Service *myserv)
{
	std::string ap = "0.0.0.0:50051";
	ServerBuilder builder;
	builder.AddListeningPort(ap, grpc::InsecureServerCredentials());
	builder.RegisterService(myserv);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << ap << std::endl;
	server->Wait();
}

class RaspberryServer : public motioncontroller::DeviceService::Service
{

protected:
	dac8532 dac;
	ads1256 adc;

public:
	grpc::Status SayHello(grpc::ServerContext *context,
						  const motioncontroller::HelloRequest *request,
						  motioncontroller::HelloReply *response)
	{
		Q_UNUSED(context);
		response->set_message(request->name());
		return grpc::Status::OK;
	}
	grpc::Status GetDigitalValues(
		grpc::ServerContext *context, const google::protobuf::Empty *request,
		::grpc::ServerWriter<motioncontroller::Analog2Digital> *writer)
	{
		Q_UNUSED(context);
		Q_UNUSED(request);
		motioncontroller::Analog2Digital msg;
		while (1) {
			adc.getAll();
			for (int c = 1; c < 8; ++c) {
				msg.GetReflection()->SetFloat(
					&msg, msg.GetDescriptor()->FindFieldByNumber(c),
					adc.adcBuffer[c] * 5.0 / 0x7fffff);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			bool resp_status = writer->Write(msg);
			if (!resp_status)
				break;
		}
		return grpc::Status::OK;
	}
	grpc::Status OutVoltage(grpc::ServerContext *context,
							const motioncontroller::Digital2Analog *request,
							motioncontroller::CommandResult *response)
	{
		Q_UNUSED(context);
		dac.outVoltage(channel_A, request->channel_voltage());
		dac.outVoltage(channel_B, request->channel_voltage());
		gWarn("set voltage: %s V",
			  std::to_string(request->channel_voltage()).data());
		response->set_command_result("ok");
		return grpc::Status::OK;
	}
	grpc::Status ConfigureAnalog2Digital(
		grpc::ServerContext *context,
		const motioncontroller::Analog2DigitalConfig *request,
		motioncontroller::CommandResult *response)
	{
		Q_UNUSED(context);
		adc.configure((quint8)request->gain(), (quint8)request->data_rate());
		response->set_command_result("adc gain and data rate set");
		return grpc::Status::OK;
	}
	grpc::Status
	SetDiffChannel(grpc::ServerContext *context,
				   const motioncontroller::SetDiffChnAnalog2Digital *request,
				   motioncontroller::CommandResult *response)
	{
		Q_UNUSED(context);
		adc.setMode(request->channel_id());
		response->set_command_result("set adc scan mode");
		return grpc::Status::OK;
	}
};

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	loguru::g_stderr_verbosity = 3;
	loguru::init(argc, argv);
	gInfoS() << "cilettttt";
	DriverContext::instance();
	std::thread threadServer([=]() { runMyServer(new RaspberryServer); });
	return a.exec();
}
