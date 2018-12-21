package com.db;
import java.io.*;
import java.sql.*;
import java.util.*;
import java.util.Scanner;

//B411236 한인수
//Database JDBC project
//파일의 절대주소 path, DBMS의 ID, PW 3가지 변수를 수정해주어야합니다.
public class B411236_hw2 {

	public static void main(String args[]) {
		// 개인정보에 따라 user, passwd는 비워두었습니다. 계정 정보를 입력하면 됩니다.
		String user = "";		// -> Oracle DBMS ID
		String passwd = "";		// -> Oracle DBMS PW
		
		String url = "jdbc:oracle:thin:@localhost:1521:xe";
		Scanner sc = new Scanner(System.in);
		Connection conn;
		Statement stat;
		
		int check_num = sc.nextInt();		// 수행하고자 하는 명령어가 insert인지 select인지 판별하는 parameter
		String check_txt = sc.nextLine();	// 입력되는 2번째 parameter
		check_txt = check_txt.substring(1);

		try {
			// oracle과 java 연결 설정
			Class.forName("oracle.jdbc.driver.OracleDriver");
			conn = DriverManager.getConnection (url, user, passwd);
			stat = conn.createStatement();

			// 수행하고자 하는 명령어가 insert인 경우
			if (check_num==1) {
				//파일의 경로를 절대주소로 명시하였습니다.
				String path = "C:\\\\Users\\\\01054\\\\Desktop\\\\Java\\\\server-workspace\\\\team_data\\\\src\\\\com\\\\db\\\\all_tables\\";
				FileReader fr = new FileReader(path+check_txt);	// txt파일 입력
				BufferedReader br = new BufferedReader(fr);		// txt파일 내용 저장
				String ch;										// txt파일의 내용이 한줄씩 저장되는 변수
				String [] check_file = check_txt.split("\\.");	// parameter의 (.txt)부분 파싱
				String q="";									// 실질정직 쿼리문이 저장되는 변수
				while((ch=br.readLine())!=null) {								// txt파일의 개행이 끝날 때 까지 반복. 즉, 모든 txt내용에 대해 수행
					StringTokenizer temp1 = new StringTokenizer(ch);			
					int check=0;												// 데이터 중, "a,b,c"가 하나의 데이터인 경우가 존재. 하나의 " 전후를 구분하는 boolean 역할의 변수
					String really_input = "";									// q에 저장하기 전에, 파싱한 문자열을 임시 저장하는 버퍼 역할
					
					while(temp1.hasMoreElements()) {							
						if(check==0) {											// 데이터 중 "a,b,c"형식이 없거나, 있는 경우, " 전의 내용에 대한 코드
							String [] temp2 = temp1.nextToken("\"").split(","); // 문자열을 ","를 기준으로 파싱. temp2[]배열에 저장한다.
							for(int j=0; j<temp2.length; j++) {					// 파싱한 데이터를 쿼리에 넣기 위해서는 'a'형식으로 감싸줘야한다. 이에 해당하는 쿼리 형식을 맞춰주는 부분								
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
							check+=1;											// "a,b,c"형식의 데이터가 있으면, 다음 반복 구문에서 check==1의 경우를 수행한다.
						}
						else if(check==1) {										// " 후의 내용에 대한 코드
							String [] temp4 = temp1.nextToken("\"").split(",");	// "a,b,c" 를 a b c 3개의 문자열로 파싱. 이를 'a, b, c' 형식으로 수정할 예정
							really_input += "'";								// ' 열기
							for(int j=0; j<temp4.length; j++) {					// "a,b,c"의 모든 문자열에 대해 수행
								really_input += temp4[j];
								really_input += ",";
							}
							really_input += "',";								// ' 닫기
							check-=1;											// 이 후에는 "a,b,c"형식이 없거나, 있는 경우에는 " 전의 내용에 대한 코드를 수행하도록 설정
						}
					}

					int really_length = really_input.length();
					really_input = really_input.substring(0, really_length-3);
					really_input += "'";
					q = "insert into "+ check_file[0] + " values("+really_input+")";	// 실질적인 쿼리문 완성
					try {
						System.out.println(q);
						stat.executeUpdate(q); 
						System.out.println("input complete");
					} catch(Exception e) {												// insert 수행 중 실패하는 경우의 error
						e.printStackTrace();
						System.out.println("error 2");
					}
				}					
				stat.close();
				br.close();
			}
			
			// 수행하고자하는 명령어가 select인 경우
			else if(check_num==2) {
				String q = "Select * from "+check_txt;									// 실질적인 쿼리 포맷 설정. text 이름만 설정하면 된다.
				stat = conn.createStatement();
				ResultSet rs = stat.executeQuery(q); 									// 실질적인 쿼리를 수행함으로서 얻은 결과문
				int first_check=0;
				while(rs.next()) {														
					int i=1;
					int temp=0;
					try {
						while(rs.getString(i)!=null){		
							temp = i+1;
							System.out.print(rs.getString(i));							// 데이터 출력
							if(rs.getString(temp)!=null) {								// 마지막이 아닌 경우 , 출력
								System.out.print(", ");
							}
							i++;
							first_check+=1;
						}	
						if(rs.getString(i+1)!=null) {									// 위의 while에서 현재 내용이 null인 경우 skip하는데, null을 출력해주는 코드
							System.out.print(", null , ");
							System.out.print(rs.getString(i+1));
							first_check+=1;
						}
					} catch (Exception e) {}
					System.out.println("");												// 하나의 데이터 셋을 출력한 뒤, 개행
				}
				if(first_check==0)
					System.out.print("No record inserted yet");
				stat.close();
			}
			else {
				System.out.println("error 3");											// select 수행 중 실패하는 경우의 error
			}
			conn.close();
		} catch ( Exception e ) {			
			e.printStackTrace();
			System.out.println("error 1");												// 코드 전반적인 부분에서 프로그래밍적 실수에 나타나는 error
		}
	}
}
