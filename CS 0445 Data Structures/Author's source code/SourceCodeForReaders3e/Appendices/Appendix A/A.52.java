char seatLocationCode;// < Code here assigns a value to seatLocationCode >// . . . double price = -0.01;switch (seatLocationCode){   case 'B':   case 'b':      System.out.println("Balcony.");      price = 15.00;      break;   case 'M': case 'm':      System.out.println("Mezzanine.");      price = 30.00;      break;   case 'O': case 'o':      System.out.println("Orchestra.");      price = 40.00;      break;   default:      System.out.println("Unknown ticket code.");      break;} // end switch