#include "Scrolling.h"
#include "MyCanvas.h"

Scrolling::Scrolling()
{

}

Scrolling::~Scrolling()
{

}

void	Scrolling::loadBackground(std::string const & str, std::string const & str2)
{
  if (!Back1.LoadFromFile(str.c_str()))
    {
      std::cout<<"Erreur durant le chargement de l'image"<<std::endl;
      exit(-1);
    }
  if (!Back2.LoadFromFile(str2.c_str()))
    {
      std::cout<<"Erreur durant le chargement de l'image"<<std::endl;
      exit(-1);
    }
  else
    {
      First.SetImage(Back1);
      Second.SetImage(Back2);
      FSize = First.GetSize();
      SSize = Second.GetSize();
      Second.SetPosition(SSize.x, 0);
    }
}

void	Scrolling::scroll()
{
  First.Move(-1, 0);
  Second.Move(-1, 0);
  FPos = First.GetPosition();
  SPos = Second.GetPosition();
  if (FPos.x <= -FSize.x || SPos.x <= -SSize.x)
    {
      Tmp = First;
      First = Second;
      Second = Tmp;
      First.SetPosition(0, 0);
      Second.SetPosition(SSize.x, 0);
    }
}

void	Scrolling::affBackground(MyCanvas *app)
{
  app->Draw(First);
  app->Draw(Second);
}
