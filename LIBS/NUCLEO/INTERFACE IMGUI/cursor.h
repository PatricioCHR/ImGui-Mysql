class cursor_imgui
{
	ImVec2 imguimousepos;
	
	void refresh (void);
	void circle (void);
	void doble_circle (void);
}

void refresh (void)
{
	imguimousepos=ImGui::GetMousePos();
}

void circle (void)
{
	ImGui::GetForegroundDrawList()->AddCircle(imguimousepos, 10.0f, IM_COL32(255,0,0,255));		
	ImGui::GetForegroundDrawList()->AddCircle(imguimousepos, 13.0f, IM_COL32(255,0,0,255));
}
	
void doble_circle (void)
{
	ImGui::GetForegroundDrawList()->AddCircle(imguimousepos, 10.0f, IM_COL32(255,0,0,255));		
	ImGui::GetForegroundDrawList()->AddCircle(imguimousepos, 13.0f, IM_COL32(255,0,0,255));
}

	
	