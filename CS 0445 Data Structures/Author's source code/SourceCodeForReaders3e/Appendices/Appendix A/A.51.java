int seatLocationCode;// < Code here assigns a value to seatLocationCode >// . . . double price;switch (seatLocationCode){   case 1:      System.out.println("Balcony.");      price = 15.00;      break;   case 2:      System.out.println("Mezzanine.");      price = 30.00;      break;   case 3:      System.out.println("Orchestra.");      price = 40.00;      break;   default:      System.out.println("Unknown ticket code.");      break;} // end switch