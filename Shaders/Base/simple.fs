R""(#version 460

out vec4 FragColor;

uniform float alpha;

void main()
{
	FragColor = alpha * vec4(1.0f, 0.79f, 0.05f, 1.0f);
}

)""