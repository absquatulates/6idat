-- Date_Handling.adb --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program
-- hugho678: Samarbetat med oskby691, Oskar Bylund, samma program

with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

package body Date_Handling is
   
   type Okday_Array is
     array (1..12) of Integer;
   
   Okday: constant Okday_Array := (31,29,31,30,31,30,31,31,30,31,30,31);
   
   procedure Get_Correct_String (S : out String) is
      
      C: Character;  
      
   begin
      
      loop
	 Get(C);
	 exit when C /= ' ';
      end loop;
      
      for I in S'Range loop
	 
	 if I /= S'Last and End_Of_Line then
	    raise Length_Error;
	 end if;
	 
	 S(I) := C;

	 if I = S'Last then
	    S(I) := C;
	 else
	    Get(C);
	 end if;
	 
      end loop; 
      
   end Get_Correct_String; 
   
   
   procedure Format (S : in String) is -- Kontrollerar om Format_Error ska kastas
      
   begin 
      
      for I in S'Range loop
	 if I=5 or I=8 then
	    if S(I) /= '-' then
	       raise Format_Error;
	    end if;
	 else
	    if S(I) not in '0'..'9' then
	       raise Format_Error;
	    end if;
	 end if;
      end loop;
      
   end Format;
   
   procedure Year_Month (Date : in Date_Type) is -- Kontrollerar om Year_Error eller Month_Error ska kastas
      
   begin 
      
      if Date.Year < 1532 or Date.Year > 9000 then
	 raise Year_Error;
      elsif Date.Month < 1 or Date.Month > 12 then
	 raise Month_Error;
      end if;     
      
   end Year_Month;
   
   procedure Februari (Date : in Date_Type) is -- Kontrollerar om Day_Error ska kastas vid månad Februari (Day.Month = 2)
      
      Skott: Boolean;  -- Boolean för Skottår
      
   begin
      
      if Date.Year mod 4 = 0 and Date.Year mod 100 /= 0 then
	 Skott := True;
      elsif Date.Year mod 400 = 0 then
	 Skott := True;
      else
	 Skott := False;
      end if;
      
      if Skott then
	 if Date.Day > 29 then
	    raise Day_Error;
	 end if;
      else
	 if Date.Day > 28 then
	    raise Day_Error;
	 end if;
      end if;
      
   end Februari;
   
   procedure Day (Date : in out Date_Type) is -- Kontrollerar om Day_Error ska kastas
      

   begin
      
      if Date.Day < 1 or Date.Day > 31 then
	 raise Day_Error;
      end if;

      if Date.Month = 4 or Date.Month = 6 or Date.Month = 9 or Date.Month = 11 then 
	 if Date.Day > 30 then
	    raise Day_Error;
	 end if;
      end if;
      
      if Date.Month = 2 then
      	 Februari(Date);
      end if;     
      
   end Day;
   
   procedure Get (Date : out Date_Type) is
      
      S : String(1..10);
      
   begin

      Get_Correct_String(S);
      Format(S);
      
      Date.Year  :=  Integer'Value(S(1..4));
      Date.Month :=  Integer'Value(S(6..7));
      Date.Day   :=  Integer'Value(S(9..10));
      
      Year_Month(Date);
      Day(Date);
      
   exception
      when Length_Error =>
	 raise Format_Error;
	 
   end Get;
   
   procedure Put (Date : in Date_Type) is
      
   begin
      
      Put(Date.Year, 0);
      Put("-");
      
      if Date.Month < 10 then
      	 Put(0, 0);
      end if;
      Put(Date.Month, 0);
      
      Put("-");
      
      if Date.Day < 10 then
      	 Put(0, 0);
      End if;
      Put(Date.Day, 0);

      
   end Put; 
   
   function Skott (Date: in Date_Type) return Boolean is
      
   begin
      
      if Date.Year mod 4 = 0 and Date.Year mod 100 /= 0 then
	 Return True;
      elsif Date.Year mod 400 = 0 then
	 Return True;
      else
	 Return False;
      end if;
      
   end Skott;
   
   function Next_Date (Date: in Date_Type) return Date_Type is

      NDate : Date_Type := Date;
      
   begin
      
      if not Skott(Date) and Date.Month = 2 and Date.Day = 28 then
	 NDate.Day := 1;
	 NDate.Month := 3;
	 
      elsif Okday(Date.Month) = Date.Day then
	 NDate.Day := 1;
	 if Date.Month = 12 then
	    NDate.Month := 1;
	    NDate.Year := Date.Year + 1;
	 else
	    NDate.Month := Date.Month + 1;
	 end if;
      else
	 NDate.Day := Date.Day + 1;
      end if;
      
      Year_Month(NDate);
      Day(NDate);
      
      return NDate;
      
   end Next_Date;
   
   function Previous_Date (Date: in Date_Type) return Date_Type is
      
      PDate : Date_Type := Date;
      
   begin     
      
      if not Skott(Date) and Date.Month = 3 and Date.Day = 1 then
	 PDate.Day := 28;
	 PDate.Month := 2;
      elsif Date.Day = 1 then
	 if Date.Month = 1 then
	    PDate.Month := 12;
	    PDate.Year := Date.Year - 1;	    
	 else 
	    PDate.Month := Date.Month - 1;
	 end if;
	 PDate.Day := Okday(PDate.Month);
      else
	 PDate.Day := Date.Day - 1;
      end if;
      
      Year_Month(PDate);
      Day(PDate);
      
      return PDate;
      
   end Previous_Date;
      
   function ">" (Date_1, Date_2: in Date_Type) return Boolean is
      
   begin
      
      if Date_1.Year > Date_2.Year then
	 return True;
      elsif Date_1.Year = Date_2.Year and Date_1.Month > Date_2.Month then
	 return True;
      elsif Date_1.Year = Date_2.Year and Date_1.Month = Date_2.Month and Date_1.Day > Date_2.Day then
	 return True;
      else
	 return False;
      end if;
      
   end ">";
   
   function "<" (Date_1, Date_2: in Date_Type) return Boolean is
      
   begin     
      
      if Date_2 > Date_1 then
	 return True;
      else 
	 return False;
      end if;

   end "<";
   
   function "=" (Date_1, Date_2: in Date_Type) return Boolean is
      
   begin
      
      if Date_1 > Date_2 or Date_1 < Date_2 then
	 return False;
      else
	 return True;
      end if;
      
   end "=";
     
end Date_Handling;
