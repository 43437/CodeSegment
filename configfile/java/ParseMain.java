package main;

import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.Map;

import org.ini4j.Ini;
import org.ini4j.InvalidFileFormatException;
import org.ini4j.MultiMap;

public class ParseMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			System.out.println("**********begin**********");
			
			System.out.println("*****read*****");
			Ini ini=new Ini(new File("test.cfg"));
			String val=ini.get("header", "first");
			System.out.println("val: "+val);
			
			MultiMap<String, String> map=ini.get("header");
			System.out.println(map.toString());
			
			Iterator< Map.Entry<String, String> > itDatas = map.entrySet().iterator();
			
			String strKey="";
			String strValue="";
			while(itDatas.hasNext()){
				
				Map.Entry<String, String> data=itDatas.next();
				strKey=data.getKey();
				strValue=data.getValue();
				System.out.println("key: "+strKey+" value: "+strValue);
				
			}
			
			System.out.println("*****write*****");
			File fw=new File("testw.cfg");
			if (fw.isFile()){
				System.out.println("file is exist.");
			}else{
				System.out.println("file is not exist.");
				fw.createNewFile();
			}
			Ini iniw=new Ini(fw);
			iniw.add("main", "first1", "1");
			iniw.add("main", "second2", "2");
			iniw.add("main", "third3", "3");
			iniw.add("default", "first_1", "_1");
			iniw.add("main", "second1", "_2");
			iniw.store();
			System.out.println("**********end**********");
		} catch (InvalidFileFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
