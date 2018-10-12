package com.example.psl;

import com.example.psl.mqtt.MqttServer;
import com.example.psl.tcp.TcpServer;

public class App {
	public static void main(String[] args) throws Exception {
		new TcpServer(9096).start();
		MqttServer.getInstance().Init();
	}
}
