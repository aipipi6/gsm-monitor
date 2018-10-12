package com.example.psl;

import com.example.psl.mqtt.MqttServer;
import com.example.psl.tcp.TcpServer;

public class App {
	public static void main(String[] args) throws Exception {
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				TcpServer.start(9096);
			}
		}).start();
		MqttServer.getInstance().Init();
	}
}
