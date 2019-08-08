package cn.max.caller;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class Caller {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
//		Process p = new ProcessBuilder("../../c++/ConsoleEcho/build/consoleEcho", "java").start();
//		Process p = new ProcessBuilder("python", "../../python/consoleEcho.py", "java").start();
		Process p = new ProcessBuilder("node", "../../nodejs/consoleEcho.js", "java").start();
		
		InputStream is = p.getInputStream();
		
		ByteArrayOutputStream outSteam = new ByteArrayOutputStream();
		byte[] buffer = new byte[1024];  
	    int len = -1;  
	    while ((len = is.read(buffer)) != -1) {  
	        outSteam.write(buffer, 0, len);  
	    }  
	    
	    String strAns = outSteam.toString();
	    System.out.println(strAns);
	    is.close();
	    outSteam.close();
	}

}
