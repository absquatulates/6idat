-- Lektion, PEKARE --

with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Test is
   
   type Element_Type;
   
   type List_Type is access Element_Type;
   
   type Element_Type is
      record
	 
	 Tal: Integer;
	 Next: List_Type;
	 
      end record;
   

   
   
   procedure Insert_First (List: in out List_Type;
			  Nytt_Tal: in Integer) is
      
      E: Element_Type;
      
   begin
      
      if List = null then
	 List := new Element_Type;
	 List.all.Tal := Nytt_Tal;
	 List.all.Next := null;
      else
	 E := new Element_Type;
	 E.all.Tal := Nytt_Tal;
	 E.all.Next := List;
      end if;
            
   end Insert_First;
   
begin

end Test;
