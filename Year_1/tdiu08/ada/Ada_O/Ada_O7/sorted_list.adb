-- sorted_list.adb --
-- hugho678: Samarbetat med carbj841, Carl Björlin, samma program

with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Unchecked_Deallocation;

  package body Sorted_List is
  
  
  procedure Free is new Ada.Unchecked_Deallocation(Pointer, List_Type);
  
  
  function Empty (List: in List_Type) return Boolean is
     
  begin
     
     return (List = null);
     
  end Empty;
  
  
  procedure Insert (List: in out List_Type;
		    Key: in Integer) is
     Tmp: List_Type;
     
  begin
     

     if Empty(List) or else Key < List.Data then
	Tmp := List;
	List := new Pointer;
	List.Data := Key;
	List.Next := Tmp;
     elsif Key /= List.Data then
	Insert(List.Next, Key);
     end if;
     
  end Insert;
  
  
  procedure Put (List: in List_Type) is
     
  begin
     
     if Empty(List) then
	null;
     else
       	Put (' ');
	Put(List.Data, Width => 0);
	Put(List.Next);
     end if;
     
  end Put;
  
  
  function Member (List: in List_Type;
		   Value: in Integer) return Boolean is
     
  begin
     
     if Empty(List) then
	return False;
     elsif List.Data = Value then
	return True;
     else
	return Member(List.Next, Value);
     end if;
     
  end Member;
  
  
  procedure Remove (List: in out List_Type;
		    Key: in Integer) is
     Tmp: List_Type;
   
  begin
     
     if Empty(List)  then
	raise No_Such_Element_Error;
    elsif List.Data = Key then	
	Tmp := List;	
	List := Tmp.Next;
	Free(Tmp);
     else
     	Remove(List.Next, Key);
     end if;
	
  end Remove;
  
  
  procedure Delete (List: in out List_Type) is
     
     Tmp : List_Type;
     
  begin
     
     if not Empty(List) then
	Tmp := List.Next;
	Free(List);
	List := Tmp;
	Delete(List);
     end if;
     
  end Delete;
  
  
  function Length (List: in List_Type) return Integer is
     
  begin
     
     if List = null then
	return 0;
     else
	return 1 + Length(List.Next);
     end if;
     
  end Length; 
   
end Sorted_List;
