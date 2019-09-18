
// import Scanner

import java.util.Scanner;

import javax.sound.sampled.SourceDataLine;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ArrayList;

class TAPRules {

    public static void parseLine(SimpleDateFormat format, String line, ArrayList<Date> parsedData) {
        String[] dates = line.split(" ");

        for (String d : dates) {

            try {
                parsedData.add(format.parse(d));
            } catch (ParseException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    public static int diffSecs(Date a, Date b)
    {
        float diff = a.getTime() - b.getTime();
        return (int) (diff / (1000));
    }


    public static void main(String[] args) 
    {
        ArrayList<Date> A = new ArrayList<Date>();
        ArrayList<Date> B = new ArrayList<Date>();
        SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");
        Scanner in = new Scanner( System.in );
        
        int Na, Nb, S;


        do{
            Na = in.nextInt();
            Nb = in.nextInt();
            S = in.nextInt();
            in.nextLine();
            
            if(Na < 1) //No more cases
            {
                break;
            }

            
            
            A.clear(); parseLine(format, in.nextLine(), A);
            B.clear(); parseLine(format, in.nextLine(), B);



            
            System.out.println(A.size());
            System.out.println(B.size());
            

            


        }while(true);
        



        in.close();
        // System.out.println("%d %d %d", Na, Nb, S);

    }
}

