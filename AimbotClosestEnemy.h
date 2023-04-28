#ifndef AIMBOT_H
#define AIMBOT_H




//AIMKILL WORK
static void *AimKillVerify(void *bot, int id_killer, int myPoints, bool isHeadshot, int weaponType, int damage){
	void *(*AimKillVerify)(void *bot, int id_killer, int myPoints, bool isHeadshot, int weaponType, int damage) = (void *(*)(void *, int, int, bool, int, int))getAbsoluteAddress("libil2cpp.so", 0x1863384);//KUBOOM
	return AimKillVerify(bot, id_killer, myPoints, isHeadshot, weaponType, damage);
}
////END

void *Jogadorinimigo = NULL;
void *MeuJogador = NULL;
bool (*get_isLocal2)(void* player);
int (*getTeam)(void* player);
void (*set_rotation)(void *player, Quaternion rotation);
Vector3 (*Transform_GetForward)(void *player);
void (*Aimbot_CMODs)(void *LocalPlayer); 
void AimbotUpdate(void *LocalPlayer) { 
  if(LocalPlayer != NULL){
   Aimbot_CMODs(LocalPlayer);//AIMBOT 100%
   void* _owner = *(void**)((uint64_t)LocalPlayer + 0x30);
	if (_owner != NULL) {
	  if(get_isLocal2(_owner)) {
      MeuJogador = LocalPlayer;
	 }
     if(MeuJogador) {
     if(getTeam(MeuJogador) != getTeam(LocalPlayer)) {
       Jogadorinimigo = LocalPlayer;
     }    
       if(Jogadorinimigo) {
		  float maxDist = 99999.0f;
          float maxAngle = Bools_t::angle;
		  if (PlayerAlive(LocalPlayer)) {//JOGADOR ESTA VIVO???
		    if (Bools_t::ativarAimbot) {
			
			  Vector3 enemyLocation = GetPlayerLocation(Jogadorinimigo);
			  
			  Vector3 Position = GetPlayerLocation(getTransform(get_main()));
			  
			    Vector3 GetHead = Vector3(enemyLocation.X, enemyLocation.Y + 1.50f, enemyLocation.Z);
				
				Quaternion PlayerLook = Quaternion::LookRotation(GetHead - Position);//Bloquar Rotacao nesses Locais
               
				Vector3 targetDir = Vector3::Normalized(enemyLocation - Position);
				
				float distanceToMe = Vector3::Distance(Position, enemyLocation);
				
				float angle = Vector3::Angle(targetDir, Transform_GetForward(getTransform(get_main()))) * 100.0;
				
				if(angle <= maxAngle){
                 if(distanceToMe < maxDist){
				  maxDist = distanceToMe;//LookHeadPos = enemyLocation;//MIRA NO PLAYER
				 if(Bools_t::AimBotHS){ 
                   set_rotation(getTransform(get_main()),PlayerLook);  
				 }
				 if (Bools_t::AutoKill){
				     AimKillVerify(Jogadorinimigo,2,99999,true,-8,9999);
					}
				}
			  }else {
              Jogadorinimigo = NULL;
              return;
			    }
              }
          }
        }
		Aimbot_CMODs(LocalPlayer);
	   }
	 }
   }
}

#endif

/*

BY CMODS
Telegram
@eucmods

YOUTUBE 
CMODS
*/