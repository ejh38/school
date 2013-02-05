
/*  Zach Sadler
	9/27/2011
	Assignment 1
*/

import java.util.*;
import java.text.*;

public class Assign1
{
	public static void main(String [] args)
	{
		// to display the dollar amounts correctly
		NumberFormat formatter = NumberFormat.getCurrencyInstance(Locale.US);
		Scanner inScan = new Scanner(System.in);
		boolean exit = false;
		int temp=0 ;		
		
		
		while (temp != 1 && temp != 2)		//keeps asking until a 1 or 2 given
		{	
			System.out.print("Is there a customer? (1 if yes, 2 if no) >> ");
			temp = inScan.nextInt();
			if (temp == 2)
				exit = true;
		}
		
		//---------------start of the main loop--------------------------//
		while (!exit)
		{
			/* The variables are set inside the loop so that new customers
			 * don't have to worry about their values being taken
			 * from the previous customer
			 */ 
			 
			temp = 0;
			int balance = -1;		//balance starts negative so the while loop is entered
			int want, member=0, wantReg = 0, wantPlus = 0, wantPro = 0, wantBurr = 0;
			double gasDisc = .00, reg = 3.50, plus = 3.75, propane = 20.00;
			double burrito1 = 1.00, burrito2 = 0.90, burrito3 = 0.80;
			String regS = "", plusS = "", proS = "", burr1S = "", burr2S = "", burr3S = "";
			double disc10 = 0, subtotal=0, payment=0;
			int regL = 0, plusL = 0, proL = 0, burr1L = 0, burr2L = 0, burr3L = 0;
		
			int subL, discL, newL, taxL, totalL, payL, changeL;
			
			System.out.println("Welcome to Gas Gas and Gas!\n");
			while (member != 1 && member != 2)
			{
				System.out.print("Do you have your GasVantage card? (1 if yes, 2 if no) >> ");
				member = inScan.nextInt();
			}
			
			if (member == 1)   //--------start of the member block------------//
				{
					System.out.println("Welcome back, esteemed card holder.\n");
					while(balance < 0)
					{
					System.out.print("What is your current GasVantage balance? >> ");
					balance = inScan.nextInt();
					if (balance < 0)
						System.out.println("Invalid entry: Can't have a negative balance.\n");
					if (balance > 1000)
					{
						System.out.println("Sorry, the maximum balance is 1000. Your balance has been adjusted accordingly.\n");
						balance = 1000;
						}
					}
				System.out.println("Your balance is " + balance + "\n");
				propane -= 2.00;
				burrito1 -= .10; burrito2 -= .10; burrito3 -= .10;
				for(gasDisc = .00; balance >=50 ; balance -= 50, gasDisc += .1)	//divides by 50
				{}
				System.out.println("---------------------------------------------");
				System.out.println("You are eligible for the following discounts:");
				System.out.println("\t\t" + formatter.format(gasDisc) + " /gal. discount on gas (reg or plus)");
				System.out.println("\t\t$2.00 /ea discount on 20 lb propane tanks");
				System.out.println("\t\t$0.10 /ea discount on burritos");
				System.out.println("---------------------------------------------");
				reg -= gasDisc; plus -= gasDisc;
				
				}	//-------------end of the member block-----------//
			else
				{
					System.out.println("What a shame. You're missing great savings!");
				}
				
			temp = 0;
			
			
			//-----------start of the purchasing loop----------//
			
			do
			{
				System.out.println("\nHere is your menu:");
				System.out.println("\t1 -->\tGasoline: " + formatter.format(reg) + " /gal for reg");
				System.out.println("\t2 -->\t          " + formatter.format(plus) + " /gal for plus");
				System.out.println("\t3 -->\tPropane: " + formatter.format(propane) + " /20 lb tank");
				System.out.println("\t4 -->\tBurritos: " + formatter.format(burrito1) + " each, with volume discounts");
				System.out.println("\t5 -->\tFinished purchasing");
				System.out.println("\t\t-------------------------\n");
				System.out.println("Enter your choice (1-5) >> ");
				
				temp = inScan.nextInt();
				System.out.println("\n");
			
			
			
			//-----------regular gas loop---------------//
				if (temp == 1)
				{
					do {
						want = -1;
						System.out.print("How many gallons of regular would you like? >> ");
						want += 1 + inScan.nextInt();
						if (want < 0)
							System.out.println("Invalid entry: Can't buy negative amounts.\n");
						if (want >= 0)
						{	
							wantReg += want;
							System.out.println("Got it. You currently have " + wantReg + " gallons in your cart.");
						}
					}
					while(want < 0);
				}	
				//------------end of reg-------//
			
				//---------start of plus loop-----//
				if (temp == 2)
				{
					do {
						want = -1;
						System.out.print("How many gallons of plus would you like? >> ");
						want += 1 + inScan.nextInt();
						if (want < 0)
							System.out.println("Invalid entry: Can't buy negative amounts.\n");	
						if (want >= 0)
						{	
							wantPlus += want;
							System.out.println("Got it. You currently have " + wantPlus + " gallons in your cart.");
						}
					}
					while(want < 0);
				}	
				//----------end of plus---------//
				
				//---------start of propane loop-----//
				if (temp == 3)
				{
					do {
						want = -1;
						System.out.print("How many propane tanks would you like? >> ");
						want += 1 + inScan.nextInt();
						if (want < 0)
							System.out.println("Invalid entry: Can't buy negative amounts.\n");	
						if (want >= 0)
						{	
							wantPro += want;
							System.out.println("Got it. You currently have " + wantPro + " tanks in your cart.");
						}
					}
					while(want < 0);
				}	
				//----------end of propane---------//
				
				//---------start of burrito loop-----//
				if (temp == 4)
				{
					do {
						want = -1;
						System.out.print("How many burritos would you like? >> ");
						want += 1 + inScan.nextInt();
						if (want < 0)
							System.out.println("Invalid entry: Can't buy negative amounts.\n");								
						if (want >= 0)
						{	
							wantBurr += want;
							System.out.println("Got it. You currently have " + wantBurr + " burritos in your cart.");
						}
					}
					while(want < 0);
				}	
				//----------end of burrito---------//
				
			}	while (temp != 5);
			
			//------------end of the purchasing loop--------------//
			
			System.out.print("\nYour subtotal is:");
			if (wantReg > 0)
			{
				regS = "\n\tRegular gas: " + wantReg + " gallons at " + formatter.format(reg) + " per gallon:";
			//	System.out.print(regS);
				subtotal += wantReg*reg;	
				regL = regS.length();			
			}
			
			if (wantPlus > 0)
			{
				plusS = "\n\tPlus gas: " + wantPlus + " gallons at " + formatter.format(plus) + " per gallon:";
		//		System.out.print(plusS);
				subtotal += wantPlus*plus;
				plusL = plusS.length();
			}
			
			if (wantPro > 0)
			{
				proS = "\n\tPropane: " + wantPro + " tanks at " + formatter.format(propane) + " per tank:";
	//			System.out.print(proS);
				subtotal += wantPro*propane;
				proL = proS.length();
			}
			
			if (wantBurr > 0)
			{
				burr1S = "\n\tBurritos: 4 at " + formatter.format(burrito1) + " per burrito:";
				burr1L = burr1S.length();
				if (wantBurr <= 4)
				{
					burr1S = "\n\tBurritos: " + wantBurr + " at " + formatter.format(burrito1) + " per burrito:";
		//			System.out.print(burrS);
					subtotal += wantBurr*burrito1;
					burr1L = burr1S.length();
				}
				else
				{
	//				System.out.print(burrS);
					subtotal += 4*burrito1;
					burr2S = "\n\tBurritos: 4 at " + formatter.format(burrito2) + " per burrito:";
					if (wantBurr <= 8)
					{
						burr2S = "\n\tBurritos: " + (wantBurr - 4) + " at " + formatter.format(burrito2) + " per burrito:";
	//					System.out.print(burrS);
						subtotal += (wantBurr-4)*burrito2;
						burr2L = burr2S.length();
					}
					else
					{
	//					System.out.print(burrS);
						subtotal += 4*burrito2;
						burr2L = burr2S.length();
						burr3S = "\n\tBurritos: " + (wantBurr - 8) + " at " + formatter.format(burrito3) + " per burrito:";
						burr3L = burr3S.length();
	//					System.out.print(burrS);
						subtotal += (wantBurr -8)*burrito3;
					}
				}
			}
			//---------adds on spaces to the end to format correctly----//
	 		for (temp = 0; temp <= (48 - regL); temp++)
			{				regS += " ";			}
			for (temp = 0; temp <= (48 - plusL); temp++)
			{				plusS += " ";			}
			for (temp = 0; temp <= (48 - proL); temp++)
			{				proS += " ";			}
			for (temp = 0; temp <= (48 - burr1L); temp++)
			{				burr1S += " ";			}
			for (temp = 0; temp <= (48 - burr2L); temp++)
			{				burr2S += " ";			}
			for (temp = 0; temp <= (48 - burr3L); temp++)
			{				burr3S += " ";			}
	
			//----------------------------------------------------------//

			//formats all the prices currectly for the receipt
			if (wantReg > 0)
				System.out.print(regS + formatter.format(wantReg*reg));
			if (wantPlus > 0)
				System.out.print(plusS + formatter.format(wantPlus*plus));
			if (wantPro > 0)
				System.out.print(proS + formatter.format(wantPro*propane));
			if (wantBurr > 0)
			{
				if (wantBurr <= 4)
					System.out.print(burr1S + formatter.format(wantBurr*burrito1));
				else
				{
					System.out.print(burr1S + formatter.format(4*burrito1));
					if (wantBurr <= 8)
						System.out.print(burr2S + formatter.format((wantBurr-4)*burrito2));
					else
					{
						System.out.print(burr2S + formatter.format(4*burrito2));
						System.out.print(burr3S + formatter.format((wantBurr-8)*burrito3));
					}
				}
			}
			
			
			// prints out the receipt
			
			System.out.println("\n                                                       ------");
			System.out.println("\tSubtotal:                                      " + formatter.format(subtotal));
			if (member == 1)
			{
				System.out.println("\tBonus discount of 10%:                         " + formatter.format(subtotal*.1));
				disc10 = subtotal*.1;
				subtotal -= disc10;
				System.out.println("                                                       ------");
				System.out.println("\tNew subtotal:                                  " + formatter.format(subtotal));
			}
			System.out.println("\tTax:                                           " + formatter.format(subtotal*.07));	
			subtotal += subtotal*.07;
			System.out.println("                                                       ------");
			System.out.println("\tTotal:                                         " + formatter.format(subtotal) + "\n");
			if (member == 1)
				System.out.println("\tAs a GasVantage card holder, you saved: " + formatter.format(gasDisc*wantReg + gasDisc*wantPlus + 2*wantPro + .1*wantBurr + disc10));
			
			while (payment < subtotal)
			{
				System.out.print("\n\tPlease enter your payment amount:              ");
				payment = inScan.nextDouble();
				if (payment < subtotal)
					System.out.print("Your total is: " + formatter.format(subtotal) + ". You can't pay less than that.");
			}
			System.out.println("\tYour change:                                   " + formatter.format(payment-subtotal));
			System.out.println("\tThanks for stopping by! (Press enter to clear screen)");
			inScan.nextLine();
			regS = inScan.nextLine();
			
			         
							
										
			//---------------------end of the initial while(!exit) loop-------------//	
			for(temp = 0; temp < 15; temp++)
			{
				System.out.println("\n");		//this clears the screen so the next customer gets a 
			}									//nice display
			while (temp != 1 && temp != 2)
			{
				System.out.print("Is there a customer? (1 if yes, 2 if no) >> ");
				temp = inScan.nextInt();
				if (temp == 2)
					exit = true;		
			}
		}
	}
}