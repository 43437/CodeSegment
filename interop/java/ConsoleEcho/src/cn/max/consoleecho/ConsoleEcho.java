package cn.max.consoleecho;

public class ConsoleEcho {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		if (args.length > 0) {
			System.out.println("java: Hello "+args[0]);
		}else {
			System.out.println("java: Hello world.");
		}
	}

}
