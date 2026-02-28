#pragma once

struct RenderContext
{
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> window;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;
};

template <typename Derived>
class BaseRenderSession
{
protected:
    BaseRenderSession() = default;

public:
    Derived &color(const Vec3 &color)
    {
        actorColor = color;
        return static_cast<Derived &>(*this);
    }

    Derived &background_color(const Vec3 &color)
    {
        backgroundColor = color;
        return static_cast<Derived &>(*this);
    }

protected:
    RenderContext create_render_context()
    {
        RenderContext ctx;

        ctx.renderer = vtkSmartPointer<vtkRenderer>::New();
        ctx.window = vtkSmartPointer<vtkRenderWindow>::New();
        ctx.interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

        ctx.renderer->SetBackground(backgroundColor.x, backgroundColor.y, backgroundColor.z);

        ctx.window->AddRenderer(ctx.renderer);
        ctx.interactor->SetRenderWindow(ctx.window);

        return ctx;
    }

    vtkSmartPointer<vtkActor> create_actor(vtkSmartPointer<vtkPolyData> polyData)
    {
        auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(polyData);

        auto actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(actorColor.x, actorColor.y, actorColor.z);

        return actor;
    }

    void start_interaction(RenderContext &ctx, vtkSmartPointer<vtkActor> actor)
    {
        ctx.renderer->AddActor(actor);
        ctx.window->Render();
        ctx.interactor->Start();
    }

protected:
    Vec3 actorColor{1.0, 0.5, 0.3};
    Vec3 backgroundColor = {0.1, 0.2, 0.4};
};