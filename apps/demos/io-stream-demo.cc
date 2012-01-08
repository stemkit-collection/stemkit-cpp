#include <sk/io/File.h>
#include <sk/io/DataOutputStream.h>
#include <sk/net/DataOutputStream.h>
#include <sk/io/BufferedOutputStream.h>
#include <iostream>

void writeData(sk::io::DataOutput& data) {
  data.writeInt(12);
  data.writeLong(1234);
}

int main(int argc, const char* const argv[]) {
  try {
    sk::io::File f1("host_ordered_data", "w");
    sk::io::BufferedOutputStream host_stream(f1.outputStream());
    sk::io::DataOutputStream host_data(host_stream);

    sk::io::File f2("network_ordered_data", "w");
    sk::io::BufferedOutputStream network_stream(f2.outputStream());
    sk::net::DataOutputStream network_data(network_stream);

    writeData(host_data);
    writeData(network_data);
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
}
