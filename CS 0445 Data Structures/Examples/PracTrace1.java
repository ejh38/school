public class PracTrace1

{

     int data;

 

     public PracTrace1(int d)

     {    data = d; }

 

     public void change(int newdata)

     {    data = newdata;    }

 

     public String toString()

     {

          return new String("Data: " + data);

     }

 

     public static void main(String [] args)

     {

          PracTrace1 [] A1 = new PracTrace1[4];

          A1[0] = new PracTrace1(10);

          A1[1] = new PracTrace1(20);

          A1[2] = new PracTrace1(30);

          A1[3] = new PracTrace1(40);

 

          showData(A1);

 

          PracTrace1 [] A2 = A1;

          PracTrace1 [] A3 = new PracTrace1[A1.length];

          for (int i = 0; i < A1.length; i++)

              A3[i] = A1[i];

 

          A2[1].change(25);

          A2[2] = new PracTrace1(35);

 

          A1[2].change(77);

 

          A3[0].change(15);

          A2[2].change(88);

          A3[3] = new PracTrace1(45);

 

          showData(A1);

          showData(A2);

          showData(A3);

     }

 

     public static void showData(PracTrace1 [] A)

     {

          for (int i = 0; i < A.length; i++)

              System.out.println(A[i]);

          System.out.println();

     }

}