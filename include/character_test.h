/**
 * @brief It declares the tests for the character module
 * 
 * @file character_test.h
 * @author Juan Ibañez
 * @version 1.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

 #ifndef CHARACTER_TEST_H
 #define CHARACTER_TEST_H
 
 /**
  * @test Test character_create with a valid ID
  * @pre Valid ID
  * @post Pointer is not NULL
  */
 void test1_character_create();
 
 /**
  * @test Test character_create with NO_ID
  * @pre NO_ID
  * @post Pointer is NULL
  */
 void test2_character_create();
 
 /**
  * @test Test character_destroy with a valid character
  * @pre Valid character
  * @post Returns OK
  */
 void test1_character_destroy();
 
 /**
  * @test Test character_destroy with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_destroy();
 
 /**
  * @test Test character_get_id with a valid character
  * @pre Character with ID = 1
  * @post Returned ID is 1
  */
 void test1_character_get_id();
 
 /**
  * @test Test character_get_id with NULL character
  * @pre NULL character
  * @post Returns NO_ID
  */
 void test2_character_get_id();
 
 /**
  * @test Test character_set_id with a valid character
  * @pre Valid character
  * @post ID is changed correctly
  */
 void test1_character_set_id();
 
 /**
  * @test Test character_set_id with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_id();
 
 /**
  * @test Test character_get_role with a newly created character
  * @pre Newly created character
  * @post Role is UNDEFINED
  */
 void test1_character_get_role();
 
 /**
  * @test Test character_get_role with NULL character
  * @pre NULL character
  * @post Returns NO_ROLE
  */
 void test2_character_get_role();
 
 /**
  * @test Test character_set_role with a valid character
  * @pre Valid character
  * @post Role is set correctly
  */
 void test1_character_set_role();
 
 /**
  * @test Test character_set_role with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_role();
 
 /**
  * @test Test character_get_name with an assigned name
  * @pre Name "Test" assigned
  * @post Name is retrieved correctly
  */
 void test1_character_get_name();
 
 /**
  * @test Test character_get_name with NULL character
  * @pre NULL character
  * @post Returns NULL
  */
 void test2_character_get_name();
 
 /**
  * @test Test character_set_name with a valid character
  * @pre Valid character, valid name
  * @post Name is set correctly
  */
 void test1_character_set_name();
 
 /**
  * @test Test character_set_name with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_name();
 
 /**
  * @test Test character_get_gdesc with a valid graphic description
  * @pre gdesc = "Test"
  * @post gdesc is retrieved correctly
  */
 void test1_character_get_gdesc();
 
 /**
  * @test Test character_get_gdesc with NULL character
  * @pre NULL character
  * @post Returns NULL
  */
 void test2_character_get_gdesc();
 
 /**
  * @test Test character_set_gdesc with a valid character
  * @pre Valid character, valid gdesc
  * @post gdesc is set correctly
  */
 void test1_character_set_gdesc();
 
 /**
  * @test Test character_set_gdesc with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_gdesc();
 
 /**
  * @test Test character_get_closeup_at_pos with a value at position
  * @pre Character "1" at position 0
  * @post Value is retrieved correctly
  */
 void test1_character_get_closeup_at_pos();
 
 /**
  * @test Test character_get_closeup_at_pos with NULL character
  * @pre NULL character
  * @post Returns NULL
  */
 void test2_character_get_closeup_at_pos();
 
 /**
  * @test Test character_set_closeup_at_pos with a valid character
  * @pre Character "1" at position 0
  * @post Value is set correctly
  */
 void test1_character_set_closeup_at_pos();
 
 /**
  * @test Test character_set_closeup_at_pos with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_closeup_at_pos();
 
 /**
  * @test Test character_get_following with a valid character
  * @pre following = 2
  * @post Value is retrieved correctly
  */
 void test1_character_get_following();
 
 /**
  * @test Test character_get_following with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_get_following();
 
 /**
  * @test Test character_set_following with a valid character
  * @pre Valid value
  * @post Value is set correctly
  */
 void test1_character_set_following();
 
 /**
  * @test Test character_set_following with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_following();
 
 /**
  * @test Test character_get_message with a valid message
  * @pre Message "Test"
  * @post Message is retrieved correctly
  */
 void test1_character_get_message();
 
 /**
  * @test Test character_get_message with NULL character
  * @pre NULL character
  * @post Returns NULL
  */
 void test2_character_get_message();
 
 /**
  * @test Test character_set_message with a valid character
  * @pre Message "Test"
  * @post Message is set correctly
  */
 void test1_character_set_message();
 
 /**
  * @test Test character_set_message with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_message();
 
 /**
  * @test Test character_get_weapon with a valid weapon
  * @pre weapon = 10
  * @post Value is retrieved correctly
  */
 void test1_character_get_weapon();
 
 /**
  * @test Test character_get_weapon with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_get_weapon();
 
 /**
  * @test Test character_set_weapon with a valid character
  * @pre weapon = 10
  * @post Value is set correctly
  */
 void test1_character_set_weapon();
 
 /**
  * @test Test character_set_weapon with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_weapon();
 
 /**
  * @test Test character_get_armor with a valid armor
  * @pre armor = 20
  * @post Value is retrieved correctly
  */
 void test1_character_get_armor();
 
 /**
  * @test Test character_get_armor with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_get_armor();
 
 /**
  * @test Test character_set_armor with a valid character
  * @pre armor = 20
  * @post Value is set correctly
  */
 void test1_character_set_armor();
 
 /**
  * @test Test character_set_armor with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_armor();
 
 /**
  * @test Test character_get_health with a valid character
  * @pre health = 100
  * @post Value is retrieved correctly
  */
 void test1_character_get_health();
 
 /**
  * @test Test character_get_health with NULL character
  * @pre NULL character
  * @post Returns -1
  */
 void test2_character_get_health();
 
 /**
  * @test Test character_set_health with a valid character
  * @pre health = 100
  * @post Value is set correctly
  */
 void test1_character_set_health();
 
 /**
  * @test Test character_set_health with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_health();
 
 /**
  * @test Test character_get_damage with a valid character
  * @pre damage = 50
  * @post Value is retrieved correctly
  */
 void test1_character_get_damage();
 
 /**
  * @test Test character_get_damage with NULL character
  * @pre NULL character
  * @post Returns -1
  */
 void test2_character_get_damage();
 
 /**
  * @test Test character_set_damage with a valid character
  * @pre damage = 50
  * @post Value is set correctly
  */
 void test1_character_set_damage();
 
 /**
  * @test Test character_set_damage with NULL character
  * @pre NULL character
  * @post Returns ERROR
  */
 void test2_character_set_damage();
 
 #endif