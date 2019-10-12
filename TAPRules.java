// 4 2 120
// 12:40:04 03:00:59 07:40:00 03:00:00
// 02:59:14 12:41:45
// 3 2 60
// 03:00:59 07:40:00 12:40:04
// 02:59:14 12:41:45
// 0 0 0

import java.util.Scanner;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

class TAPRules {

    public static void parseLine(SimpleDateFormat format, String line, ArrayList<Date> parsedData) {
        String[] dates = line.split(" ");

        for (String d : dates) {

            try {
                parsedData.add(format.parse(d));
            } catch (ParseException e) {

                e.printStackTrace();
            }
        }
    }

    public static int diffSecs(Date a, Date b)
    {
        float diff = a.getTime() - b.getTime();
        return (int) (diff / (1000));
    }

    public static void dp(int S, ArrayList<Date> A, ArrayList<Date> B, int initA, int initB, int[] times)
    {
        if(initA < A.size() && initB < B.size())
        {
            Date a = A.get(initA);
            Date b = B.get(initB);

            int diff = Math.abs(diffSecs(a, b));

            if (diff < S) // si hace match
            {
                if(times[initB] == -1){
                    times[initB] = diff;
                }

                dp(S, A, B, initA + 1, initB, times);
            }
            else
            {
                
                if( a.compareTo(b) == -1 )
                {
                    dp(S, A, B, initA + 1, initB, times);
                }
                else
                { 
                    // en caso de que lo de a sea menor a lo de b
                    // esto es para no saltar i
                    dp(S, A, B, initA, initB + 1, times);
                }
            }


        }
    }

    public static void main(String[] args) 
    {
        ArrayList<Date> A = new ArrayList<Date>();
        ArrayList<Date> B = new ArrayList<Date>();

        SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");

        Comparator<Date> compDate = new Comparator<Date>(){
            public int compare(Date a, Date b){
                return a.compareTo(b);
            }
        };


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
            
            A.clear(); 
            B.clear(); 
            
            parseLine(format, in.nextLine(), A);
            parseLine(format, in.nextLine(), B);
            
            A.sort(compDate);
            B.sort(compDate);
            
            int[] times = new int[B.size()];

            Arrays.fill(times, -1);

            dp(S, A, B, 0, 0, times);


            int nMatches = 0;
            float avg = 0;
            for (int time : times) {
               if(time > -1) 
               {
                avg+=time;
                nMatches++;
               }
            }


            if(nMatches > 0)
            {
                avg /= nMatches;
                System.out.format("%d %.1f\n", nMatches, avg);
            }
            else
            {
                System.out.println("No matches");

            }
         
        }while(true);
        

        in.close();

    }
}

