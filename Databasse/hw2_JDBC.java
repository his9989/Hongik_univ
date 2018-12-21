package com.db;
import java.io.*;
import java.sql.*;
import java.util.*;
import java.util.Scanner;

//B411236 ���μ�
//Database JDBC project
//������ �����ּ� path, DBMS�� ID, PW 3���� ������ �������־���մϴ�.
public class B411236_hw2 {

	public static void main(String args[]) {
		// ���������� ���� user, passwd�� ����ξ����ϴ�. ���� ������ �Է��ϸ� �˴ϴ�.
		String user = "";		// -> Oracle DBMS ID
		String passwd = "";		// -> Oracle DBMS PW
		
		String url = "jdbc:oracle:thin:@localhost:1521:xe";
		Scanner sc = new Scanner(System.in);
		Connection conn;
		Statement stat;
		
		int check_num = sc.nextInt();		// �����ϰ��� �ϴ� ��ɾ insert���� select���� �Ǻ��ϴ� parameter
		String check_txt = sc.nextLine();	// �ԷµǴ� 2��° parameter
		check_txt = check_txt.substring(1);

		try {
			// oracle�� java ���� ����
			Class.forName("oracle.jdbc.driver.OracleDriver");
			conn = DriverManager.getConnection (url, user, passwd);
			stat = conn.createStatement();

			// �����ϰ��� �ϴ� ��ɾ insert�� ���
			if (check_num==1) {
				//������ ��θ� �����ּҷ� ����Ͽ����ϴ�.
				String path = "C:\\\\Users\\\\01054\\\\Desktop\\\\Java\\\\server-workspace\\\\team_data\\\\src\\\\com\\\\db\\\\all_tables\\";
				FileReader fr = new FileReader(path+check_txt);	// txt���� �Է�
				BufferedReader br = new BufferedReader(fr);		// txt���� ���� ����
				String ch;										// txt������ ������ ���پ� ����Ǵ� ����
				String [] check_file = check_txt.split("\\.");	// parameter�� (.txt)�κ� �Ľ�
				String q="";									// �������� �������� ����Ǵ� ����
				while((ch=br.readLine())!=null) {								// txt������ ������ ���� �� ���� �ݺ�. ��, ��� txt���뿡 ���� ����
					StringTokenizer temp1 = new StringTokenizer(ch);			
					int check=0;												// ������ ��, "a,b,c"�� �ϳ��� �������� ��찡 ����. �ϳ��� " ���ĸ� �����ϴ� boolean ������ ����
					String really_input = "";									// q�� �����ϱ� ����, �Ľ��� ���ڿ��� �ӽ� �����ϴ� ���� ����
					
					while(temp1.hasMoreElements()) {							
						if(check==0) {											// ������ �� "a,b,c"������ ���ų�, �ִ� ���, " ���� ���뿡 ���� �ڵ�
							String [] temp2 = temp1.nextToken("\"").split(","); // ���ڿ��� ","�� �������� �Ľ�. temp2[]�迭�� �����Ѵ�.
							for(int j=0; j<temp2.length; j++) {					// �Ľ��� �����͸� ������ �ֱ� ���ؼ��� 'a'�������� ��������Ѵ�. �̿� �ش��ϴ� ���� ������ �����ִ� �κ�								
								String [] for_flights = temp2[j].split("/");

								if(for_flights.length>1) {
									temp2[j]="TO_DATE('";
									for(int k=0; k<for_flights.length; k++) {
										temp2[j] += for_flights[k];
										temp2[j] += "-";
									}
									temp2[j] = temp2[j].substring(0,  25);
									temp2[j] += "', 'yyyy-MM-DD HH24:MI'), ";
									really_input += temp2[j];
								}
								else {
									really_input += "'";
									really_input += temp2[j];
									really_input += "', ";
								}
							}
							check+=1;											// "a,b,c"������ �����Ͱ� ������, ���� �ݺ� �������� check==1�� ��츦 �����Ѵ�.
						}
						else if(check==1) {										// " ���� ���뿡 ���� �ڵ�
							String [] temp4 = temp1.nextToken("\"").split(",");	// "a,b,c" �� a b c 3���� ���ڿ��� �Ľ�. �̸� 'a, b, c' �������� ������ ����
							really_input += "'";								// ' ����
							for(int j=0; j<temp4.length; j++) {					// "a,b,c"�� ��� ���ڿ��� ���� ����
								really_input += temp4[j];
								really_input += ",";
							}
							really_input += "',";								// ' �ݱ�
							check-=1;											// �� �Ŀ��� "a,b,c"������ ���ų�, �ִ� ��쿡�� " ���� ���뿡 ���� �ڵ带 �����ϵ��� ����
						}
					}

					int really_length = really_input.length();
					really_input = really_input.substring(0, really_length-3);
					really_input += "'";
					q = "insert into "+ check_file[0] + " values("+really_input+")";	// �������� ������ �ϼ�
					try {
						System.out.println(q);
						stat.executeUpdate(q); 
						System.out.println("input complete");
					} catch(Exception e) {												// insert ���� �� �����ϴ� ����� error
						e.printStackTrace();
						System.out.println("error 2");
					}
				}					
				stat.close();
				br.close();
			}
			
			// �����ϰ����ϴ� ��ɾ select�� ���
			else if(check_num==2) {
				String q = "Select * from "+check_txt;									// �������� ���� ���� ����. text �̸��� �����ϸ� �ȴ�.
				stat = conn.createStatement();
				ResultSet rs = stat.executeQuery(q); 									// �������� ������ ���������μ� ���� �����
				int first_check=0;
				while(rs.next()) {														
					int i=1;
					int temp=0;
					try {
						while(rs.getString(i)!=null){		
							temp = i+1;
							System.out.print(rs.getString(i));							// ������ ���
							if(rs.getString(temp)!=null) {								// �������� �ƴ� ��� , ���
								System.out.print(", ");
							}
							i++;
							first_check+=1;
						}	
						if(rs.getString(i+1)!=null) {									// ���� while���� ���� ������ null�� ��� skip�ϴµ�, null�� ������ִ� �ڵ�
							System.out.print(", null , ");
							System.out.print(rs.getString(i+1));
							first_check+=1;
						}
					} catch (Exception e) {}
					System.out.println("");												// �ϳ��� ������ ���� ����� ��, ����
				}
				if(first_check==0)
					System.out.print("No record inserted yet");
				stat.close();
			}
			else {
				System.out.println("error 3");											// select ���� �� �����ϴ� ����� error
			}
			conn.close();
		} catch ( Exception e ) {			
			e.printStackTrace();
			System.out.println("error 1");												// �ڵ� �������� �κп��� ���α׷����� �Ǽ��� ��Ÿ���� error
		}
	}
}
