class cursor_imgui
{
	public :
	ImVec2 pos;
	
	void refresh (void);
	void circle (void);
	void doble_circle (void);
};

void cursor_imgui::refresh (void)
{
	pos=ImGui::GetMousePos();
}

void cursor_imgui::circle (void)
{
	ImGui::GetForegroundDrawList()->AddCircle(pos, 10.0f, IM_COL32(255,0,0,255));		
	ImGui::GetForegroundDrawList()->AddCircle(pos, 13.0f, IM_COL32(255,0,0,255));
}
	
void cursor_imgui::doble_circle (void)
{
	ImGui::GetForegroundDrawList()->AddCircle(pos, 10.0f, IM_COL32(255,0,0,255));		
	ImGui::GetForegroundDrawList()->AddCircle(pos, 13.0f, IM_COL32(255,0,0,255));
}

	
	