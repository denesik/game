#include "GUIComponent.h"


GUIComponent::GUIComponent(int _width, int _height)
{
	width = _width;
	height = _height;
	guiComponent = new GUIContainer(width, height);
}

GUIComponent::~GUIComponent( void )
{

}

bool GUIComponent::Initialize()
{
	return true;
}

void GUIComponent::LoadContent()
{
	guiComponent->LoadContent();
}

void GUIComponent::Update()
{
	guiComponent->Update();
}

void GUIComponent::Draw( Render *render )
{
	guiComponent->Draw(render);
}

void GUIComponent::UnloadContent()
{
	guiComponent->UnloadContent();
}

void GUIComponent::SetTextureManager( TextureManager *_textureManager )
{
	guiComponent->SetTextureManager(_textureManager);
}

TextureManager * GUIComponent::GetTextureManager()
{
	return guiComponent->GetTextureManager();
}

void GUIComponent::SetDefaultFont( IFont *_font )
{
	guiComponent->SetDefaultFont(_font);
}

IFont * GUIComponent::GetDefaultFont()
{
	return guiComponent->GetDefaultFont();
}

void GUIComponent::Resize( int width, int height )
{
	guiComponent->Resize(width, height);
}

void GUIComponent::OnMouseButtonDown( int button, int x, int y )
{
	guiComponent->OnMouseButtonDown(button, x, y);
}

void GUIComponent::OnMouseButtonUp( int button, int x, int y )
{
	guiComponent->OnMouseButtonUp(button, x, y);
}

void GUIComponent::OnMouseButtonClick( int button, int x, int y )
{
	guiComponent->OnMouseButtonClick(button, x, y);
}

int GUIComponent::RemoveGUIObject( GUIObject *guiObject )
{
	return guiComponent->RemoveGUIObject(guiObject);
}

int GUIComponent::AddGUIObject( GUIObject *guiObject )
{
	return guiComponent->AddGUIObject(guiObject);
}
