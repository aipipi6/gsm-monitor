package com.example.psl.mqtt;


import org.apache.commons.codec.binary.Base64;

import com.aliyun.openservices.iot.api.Profile;
import com.aliyun.openservices.iot.api.message.MessageClientFactory;
import com.aliyun.openservices.iot.api.message.api.MessageClient;
import com.aliyun.openservices.iot.api.message.callback.MessageCallback;
import com.aliyun.openservices.iot.api.message.entity.Message;
import com.aliyun.openservices.iot.api.message.entity.MessageToken;
import com.aliyuncs.AcsResponse;
import com.aliyuncs.DefaultAcsClient;
import com.aliyuncs.RpcAcsRequest;
import com.aliyuncs.exceptions.ClientException;
import com.aliyuncs.iot.model.v20170420.PubRequest;
import com.aliyuncs.iot.model.v20170420.PubResponse;
import com.aliyuncs.profile.DefaultProfile;
import com.aliyuncs.profile.IClientProfile;

public class MqttServer {
	
	public static String sAccessKeyID = "LTAIRiw74CeU9yqx";
	public static String sAccessKeySecret = "pOoIsqHYEe43NWlJX9i7SgKn5SPMLW";
	
	public static String sUid = "1325034814234242";
	public static String sRegionId = "cn-shanghai";
	public static String sEndPoint = "https://" + sUid + ".iot-as-http2." + sRegionId + ".aliyuncs.com";	
	
	public static String sProductCode = "Iot";
	public static String sDomain = "iot.cn-shanghai.aliyuncs.com";
	
	public static String sProductKey = "a1ZD4j6zsgf";
	
	private static final MqttServer instance = new MqttServer();
	private DefaultAcsClient client;
	
	private MqttServer(){}
	
	public static MqttServer getInstance() {
		return instance;
	}
	
	
	public void Init() {
		try {
			{
			// 初始化sdk 客户端
			DefaultProfile.addEndpoint(sRegionId, 
				sRegionId, 
				sProductCode, 
				sDomain);
			IClientProfile profile = DefaultProfile.getProfile(sRegionId, sAccessKeyID, sAccessKeySecret);
			client = new DefaultAcsClient(profile); 
			
			}
			
			{
			// 配置服务端订阅
	        Profile profile = Profile.getAccessKeyProfile(
	        		sEndPoint, 
	        		sRegionId, 
	        		sAccessKeyID, 
	        		sAccessKeySecret);
	        
	        MessageClient client = MessageClientFactory.messageClient(profile);
	        client.connect(messageReviceCallBack);
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	MessageCallback messageReviceCallBack = new MessageCallback() {
		@Override
		public Action consume(MessageToken messageToken) {
			// TODO Auto-generated method stub
			Message m = messageToken.getMessage();
			String payloadContent = new String(m.getPayload());
			 	System.out.println("receive : " + payloadContent);
			return Action.CommitSuccess;
		}
    };
	
	public String publishMsg(String devName, String msg) {
		try {
			PubRequest request = new PubRequest();
			request.setProductKey(sProductKey);
			request.setMessageContent(Base64.encodeBase64String(msg.getBytes()));
			request.setTopicFullName("/" + sProductKey + "/" + devName + "/get");
			request.setQos(0); //目前支持QoS0和QoS1
			PubResponse response;
			response = client.getAcsResponse(request);
			if(response.getSuccess()) {
				System.out.println(String.format("Send message to \"%s\" success\n  %s", devName, msg));
				return "发送消息成功";
			} else {
				System.err.println(String.format("Send message to \"%s\" failed\n  %s", devName, response.getErrorMessage()));
				return response.getErrorMessage();
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return e.getMessage();
		}
	}
	
    
    @SuppressWarnings({ "unchecked", "rawtypes" })
	public AcsResponse executeTest(RpcAcsRequest request) {
		AcsResponse response = null;
			try {
				response = client.getAcsResponse(request);
			} catch (ClientException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		return response;
	}

    
}
